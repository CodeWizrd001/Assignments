section .data
	nl : db 10
	pa : db "Enter Celsius : "
	la : equ $-pa 
	five : dw 5
	nine : dw 9 
	zero : dq 0 
	thirytwo : dw 32
	format_in : db "%lf",0
	format_out : db "Fahrenheit : %lf",10,0

section .bss 
	c : resq 1
	f : resq 1 
	t_float : resq 1 

section .text 
global main
	extern scanf
	extern printf 
main :
	mov eax , 4
	mov ebx , 1 
	mov ecx , pa
	mov edx , la 
	int 80h

	call _scan_float
	fst qword[c]

	ffree ST0
	fld qword[zero]
	fiadd word[nine]
	fidiv word[five]
	fmul qword[c]
	fiadd word[thirytwo]

	mov eax , format_out
	call _print_float

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
