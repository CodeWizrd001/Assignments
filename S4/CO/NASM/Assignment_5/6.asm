section .data
	nl : db 10
	pn : db "Enter n : "
	ln : equ $-pn
	pel : db "Enter Elements : ",10
	lel : equ $-pel
	ans : db "After Sorting : ",10
	lans : equ $-ans
	format_in : db "%lf",0
	format_out : db "%lf",10,0

section .bss 
	c : resq 1
	f : resq 1 
	n : resw 1 
	t : resw 1
	min : resw 1 
	temp : resw 1
	minf : resq 1 
	count : resw 1
	array : resq 100 
	t_float : resq 1 

section .text 
global main
	extern scanf
	extern printf 
main :
	mov eax , 4
	mov ebx , 1 
	mov ecx , pn
	mov edx , ln 
	int 80h

	call read
	mov eax , 0
	mov ax , word[temp] 
	mov word[n] , ax 

	mov eax , 4
	mov ebx , 1 
	mov ecx , pel
	mov edx , lel 
	int 80h

	call read_float_array

	call sort_float_array

	mov eax , 4
	mov ebx , 1 
	mov ecx , ans
	mov edx , lans
	int 80h

	mov eax , 0
	mov ax , word[n]
	call print_float_array

	jmp exit

sort_float_array :
	pusha 
	mov eax , array
	mov ebx , 0
sort_loop :
	cmp bx , word[n]
	je retSort
	call minArr
	movzx edx , word[min]
	fld qword[array+8*edx]
	fld qword[array+8*ebx]
before_swap :
	fstp qword[array+8*edx]
	fstp qword[array+8*ebx]
	inc bx 
	jmp sort_loop
retSort :
	popa 
	ret 

; Function To Return MinIndex
minArr :
	pusha
	mov eax , array
	mov word[min] , bx
	movzx ecx , word[min]
minLoop :
	cmp bx , word[n] 
	je sMin
	call clearStack
	fld qword[array+8*ecx]
	fld qword[array+8*ebx]
before_cmp :
	fcomi ST1
	jae cMin
	mov word[min] , bx
	movzx ecx , word[min]
cMin:
	inc ebx 
	jmp minLoop
sMin :
	popa
	ret

read_float_array : 
	pusha 
	mov eax , 0
read_loop :
	cmp ax , word[n]
	je retRead
	call _scan_float
	fst qword[array+8*eax]
	inc ax 
	jmp read_loop
retRead :
	popa 
	ret

print_float_array : 
	pusha 
	mov eax , 0
print_loop :
	cmp ax , word[n]
	je retRead
	fld qword[array+8*eax]
	push eax 
	mov eax , format_out
	call _print_float
	pop eax 
	inc ax 
	jmp print_loop
retPrint :
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

; Read Multiple Digits
read :
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
print :
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
	
; Exit
exit :
	mov eax , 1
	mov ebx , 0
	int 80h
