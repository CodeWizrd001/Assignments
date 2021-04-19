section .data
	spc : db 32
	ps1 : db "Enter String 1 : "
	ls1 : equ $-ps1
	ps2 : db "Enter String 2 : "
	ls2 : equ $-ps2
	nl : db 10

section .bss
	sta : resb 100
	stb : resb 100
	stc : resb 200
	len : resb 1
	la : resb 1
	lb : resb 1
	t : resb 1
	b : resb 1 

section .text 
global _start 

_start : 
	mov eax , 4
	mov ebx , 1
	mov ecx , ps1
	mov edx , ls1
	int 80h

	mov ebx , sta
	call read_string
	mov cl , byte[len]
	mov byte[la] , cl

	mov eax , 4
	mov ebx , 1
	mov ecx , ps2
	mov edx , ls2 
	int 80h

	mov ebx , stb 
	call read_string
	mov cl , byte[len]
	mov byte[lb] , cl	

	movzx ecx , byte[lb]
	mov esi , stb
	mov edi , sta
	movzx edx , byte[la]
	add edi , edx
	cld
	rep movsb

	;movzx ecx , byte[lb]
	;mov esi , stb
	;rep movsb

	mov ecx , sta
	movzx edx , byte[la]
	add dl , byte[lb]
	call print_string


	call print_nl

	jmp exit

concat_string :
	pusha
	add eax , ebx
	mov ebx , 0
cpLoop :
	cmp ebx , edx 
	je endConc	
	push edx 
	movzx edx , byte[ecx]
	mov byte[eax] , dl
	pop edx
	inc ebx
	inc eax 
	inc ecx
	jmp cpLoop
endConc :
	popa
	ret

print_string :
	pusha
	mov eax , 4
	mov ebx , 1
	int 80h
	popa
	ret

read_string :
	pusha
	mov ecx , 0
	mov byte[len] , 0 
rsLoop :
	push ecx
	push ebx 
	mov eax , 3
	mov ebx , 0
	mov ecx , t
	mov edx , 1
	int 80h
	pop ebx
	pop ecx 
	
	cmp byte[t] , 10
	je endRS 
	movzx edx , byte[t]
	mov byte[ebx+ecx] , dl
	inc ecx 
	jmp rsLoop
endRS :
	mov byte[ebx+ecx] , 0
	mov byte[len],cl
	popa 
	ret

print_nl :
	pusha
	mov ecx , nl
	mov edx , 1
	call print_string
	popa
	ret

exit :
	mov eax , 1
	mov ebx , 0
	int 80h
