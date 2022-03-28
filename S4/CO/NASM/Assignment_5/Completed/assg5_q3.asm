section .data
	nl : db 10
	pa : db "Enter a : "
	la : equ $-pa 
	pb : db "Enter b : "
	lb : equ $-pb 
	pc : db "Enter c : "
	lc : equ $-pc
	two : dw 2
	four : dw 4 
	zero : dq 0
	quad : db "ax^2 + bx + c",10
	quadl : equ $-quad
	format_in : db "%lf",0
	imaginary : db "Imaginary Roots",10
	li : equ $-imaginary
	format_out_1 : db "Root_1 : %lf",10,0
	format_out_2 : db "Root_2 : %lf",10,0

section .bss 
	a : resq 1 
	b : resq 1 
	c : resq 1
	a2 : resq 1 
	ac4 : resq 1 
	det : resq 1 
	root_1 : resq 1 
	root_2 : resq 1
	t_float : resq 1 

section .text 
global main
	extern scanf
	extern printf 
main :
	mov eax , 4
	mov ebx , 1 
	mov ecx , quad
	mov edx , quadl 
	int 80h

	mov eax , 4
	mov ebx , 1 
	mov ecx , pa
	mov edx , la 
	int 80h

	call _scan_float
	fst qword[a]

	mov eax , 4
	mov ebx , 1 
	mov ecx , pb
	mov edx , lb 
	int 80h

	call _scan_float
	fst qword[b]

	mov eax , 4
	mov ebx , 1 
	mov ecx , pc
	mov edx , lc 
	int 80h

	call _scan_float
	fst qword[c]

	ffree ST0				; 4ac 
	fld qword[a]
	fmul qword[c] 
	fimul word[four]
	fst qword[ac4]

	ffree ST0 				; 2a 
	fld qword[a]
	fimul word[two]
	fst qword[a2]

	ffree ST0				; sqrt(b^2-4ac)
	fld qword[b]
	fmul qword[b]
found_b2:
	fsub qword[ac4]
	fst qword[det]
	fldz
found_det:
	fcomi ST1				; if b^2-4ac < 0 	print_imaginary
	ja print_imaginary
	call clearStack
	fld qword[det]
	fsqrt 
	fst qword[det]

	ffree ST0 				; (-b+det)/2a
	fld qword[b]
	fchs 
	fadd qword[det]
	fdiv qword[a2]
	fst qword[root_1]
	mov eax , format_out_1
	call _print_float

	ffree ST0 				; (-b-det)/2a
	fld qword[b]
	fchs 
	fsub qword[det]
	fdiv qword[a2]
	fst qword[root_2]
	mov eax , format_out_2
	call _print_float

	jmp exit

print_imaginary : 
	mov eax , 4 
	mov ebx , 1
	mov ecx , imaginary
	mov edx , li 
	int 80h

	jmp exit

_scan_float :
	pusha
	push ebp
	mov ebp , esp
	sub esp , 8
	lea eax , [esp]
	push eax 
	push format_in
	call scanf
	fld qword[ebp-8]
	fst qword[t_float]
	mov esp , ebp
	pop ebp
	popa 
	ret

_print_float :
	pusha
	push ebp
	mov ebp , esp
	sub esp , 8
	fst qword[ebp-8]
	push eax
	call printf
	mov esp , ebp
	pop ebp
	popa
	ret

clearStack :
	pusha
	ffree ST0
	ffree ST1
	ffree ST2
	ffree ST3
	ffree ST4
	ffree ST5
	ffree ST6
	ffree ST7
	popa
	ret
	
; Exit
exit :
	mov eax , 1
	mov ebx , 0
	int 80h
