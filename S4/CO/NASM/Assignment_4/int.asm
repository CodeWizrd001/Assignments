section .data
	nl : db 10
	format_in : db "%d"
	format_out : db "Number : %d",10

section .bss 
	a : resw 1
	b : resw 1
	c : resw 1
	t : resw 1
	temp : resw 1
	num : resw 1
	count : resb 1 

section .text 
global main
	extern scanf
	extern printf 
main :
	call _scan
	call _print
	
	jmp exit

_scan :
	pusha
	push ebp
	mov ebp , esp
	sub esp , 2
	lea eax , [ebp-2]
	push eax 
	push format_in
	call scanf
	mov ax , word[ebp-2]
	mov word[temp] , ax
	mov esp , ebp
	pop ebp
	popa 
	ret

_print :
	pusha
	push ebp
	mov ebp , esp
	sub esp , 2
	mov ax , word[temp]
	mov word[ebp-2] , ax
	push format_out
	call printf
	mov esp , ebp
	pop ebp
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
