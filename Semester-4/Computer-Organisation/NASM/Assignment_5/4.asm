section .data
	nl : db 10
	px : db "Enter X : "
	lx : equ $-px 
	pn : db "Enter Number Of Terms To Use For Estimation : "
	ln : equ $-pn 
	two : dw 2
	format_in : db "%lf",0
	format_out : db "Cos Estimation : %lf",10,0
	format_out_ : db "Cos Calculated : %lf",10,0
	format_diff : db "Difference : %lf",10,0

section .bss 
	n : resw 1 
	b : resq 1 
	f : resw 1
	t : resw 1
	i : resw 1 
	c : resq 1 
	y : resw 1
	x : resq 1
	a : resq 1
	ans : resq 1 
	pow : resd 1 
	fact : resd 1 
	temp : resw 1
	count : resw 1
	t_float : resq 1 

section .text 
global main
	extern scanf
	extern printf 
main :
	mov eax , 4
	mov ebx , 1 
	mov ecx , px
	mov edx , lx 
	int 80h

	call _scan_float
	fstp qword[x]

	mov eax , 4
	mov ebx , 1 
	mov ecx , pn
	mov edx , ln
	int 80h

	call _read_int
	mov word[n] , ax

	call cos
	call clearStack

	fld qword[ans]
	mov eax , format_out
	call _print_float
	call clearStack

	fld qword[x]
	fcos
	mov eax , format_out_
	call _print_float
before:
	fsub qword[ans] 
	mov eax , format_diff
	call _print_float

exit_:
	jmp exit

cos :
	pusha 
	fldz 
	movzx ecx , word[n]
	fst qword[ans]
	dec ecx 
	mov dword[f] , 1
c_loop :
	cmp ecx , 0
	jl retCos
	mov edx , ecx
	add dx , cx
	mov dword[y] , edx 
	fld qword[x]
	call _pow_float
	mov word[f] , dx 
	call factorial
	fidiv dword[fact]
	mov eax , ecx 
	mov ebx , 2
	mov edx , 0
	div bx 
	cmp dx , 0
	je continue 
	fchs
continue:
	fadd qword[ans]
	fstp qword[ans]
	dec ecx 
	jmp c_loop
retCos :
	popa 
	ret

_pow_float :
	fld1 
	movzx ebx , word[y]
pf_loop :
	cmp bx , 0 
	jle retPowf
	fmul qword[x]
	dec bx 
after_mul:
	jmp pf_loop
retPowf :
	ret 

power :
	pusha 
	mov eax , 1
	movzx ebx , word[y]
	movzx ecx , word[f]
p_loop :
	cmp bx , 0 
	jle retPow
	mul cx
	dec bx 
	jmp p_loop
retPow :
	mov dword[pow] , eax
	popa
	ret

factorial :
	pusha 
	mov eax , 1
	movzx ebx , word[f]
f_loop :
	cmp bx , 0 
	jle retFact
	mul bx 
	dec bx 
	jmp f_loop
retFact :
	mov dword[fact] , eax
	popa
	ret

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

; Read Multiple Digits
_read_int :
	mov word[temp] , 0
_read :
	mov eax , 3
	mov ebx , 0
	mov ecx , t
	mov edx , 1
	int 80h 
	cmp word[t] , 10
	je rRet
	sub word[t] , 30h
	mov ax , word[temp] 
	mov bx , 10
	mul bx
	add ax , word[t] 
	mov word[temp] , ax
	jmp _read
rRet :
	mov ax , word[temp] 
	ret

; Print Multiple Digits
_print_int :
	mov byte[count] , 0
	pusha
digs :
	cmp word[temp] , 0
	je print_
	inc byte[count] 
	mov edx , 0
	mov ax , word[temp]
	mov bx , 10
	div bx
	push edx
	mov word[temp] , ax
	jmp digs
print_ :
	cmp byte[count] , 0
	je pRet
	dec byte[count]
	pop edx 
	mov word[t] , dx
	add byte[t] , 30h
	mov eax , 4 
	mov ebx , 1
	mov ecx , t
	mov edx , 1
	int 80h
	jmp print_
pRet :
	mov eax , 4
	mov ebx , 1
	mov ecx , nl
	mov edx , 1
	int 80h
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
