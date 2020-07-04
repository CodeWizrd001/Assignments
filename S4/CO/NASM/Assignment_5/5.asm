section .data
	nl : db 10
	px : db "Enter X : "
	lx : equ $-px
	py : db "Enter Y : "
	ly : equ $-py
	zero : dq 0
	quad_1 : db "1st Quadrant",10
	quad_2 : db "2nd Quadrant",10
	quad_3 : db "3rd Quadrant",10
	quad_4 : db "4th Quadrant",10
	lq : equ $-quad_4
	x_axis : db "X Axis",10
	y_axis : db "Y Axis",10
	origin : db "Origin",10
	la : equ $-origin
	format_in : db "%lf",0

section .bss 
	x : resq 1
	y : resq 1 
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
	fst qword[x]

	mov eax , 4
	mov ebx , 1 
	mov ecx , py
	mov edx , ly 
	int 80h

	call _scan_float
	fst qword[y] 

	fld qword[y]
	fld qword[zero]
	fcomi ST1
	fld qword[x]
	fld qword[zero]
	ja down 
	jb up 
	jmp _x_axis
down : 
	fcomi ST1 
	jb q4 
	ja q3 
	jmp _y_axis
up :
	fcomi ST1
	jb q1
	ja q2 
	jmp _y_axis
q1 :
	mov ecx , quad_1
	mov edx , lq 
	jmp _print
q2 :
	mov ecx , quad_2
	mov edx , lq 
	jmp _print
q3 :
	mov ecx , quad_3
	mov edx , lq 
	jmp _print
q4 :
	mov ecx , quad_4
	mov edx , lq 
	jmp _print
_y_axis :
	mov ecx , y_axis
	mov edx , la
	jmp _print
_x_axis :
	fcomi ST1
	je _origin
	mov ecx , x_axis
	mov edx , la 
	jmp _print
_origin:
	mov ecx , origin
	mov edx , la 
	jmp _print

_print : 
	mov eax , 4
	mov ebx , 1
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
