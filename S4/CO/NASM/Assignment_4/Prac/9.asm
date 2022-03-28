section .data
	spc : db 32
	ps1 : db "Enter String 1 : "
	ls1 : equ $-ps1
	ps2 : db "Enter String 2 : "
	ls2 : equ $-ps2
	nl : db 10

section .bss
	count : resb 1
	temp : resb 1
	sta : resb 100
	stb : resb 100
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

	mov ecx , sta
	movzx edx , byte[la]
	call print_string
	call print_nl

	jmp exit

print_num :
	pusha
	movzx eax , byte[temp]
	mov byte[count] , 0
eLoop :
	movzx eax , byte[temp]
	cmp eax , 0
	je pLoop 
	mov edx , 0
	mov bl , 10
	div bl
	movzx edx , ah
	add edx , 30h
	push edx
	inc byte[count]
	mov byte[temp] , al
	jmp eLoop
pLoop :
	cmp byte[count] , 0
	je endPrint
	pop edx
	mov byte[temp] , dl
	mov eax , 4
	mov ebx , 1
	mov ecx , temp
	mov edx , 1
	int 80h
	dec byte[count]
	jmp pLoop
endPrint : 
	popa	
	ret

count_string :
	pusha
	mov ecx , 0
	mov byte[len] , 0
cLoop :
	cmp ecx , ebx
	je endCon
	mov dl , byte[eax+ecx]
	cmp dl , 32
	jne cCont
	inc byte[len]
cCont : 
	inc ecx
	jmp cLoop
endCon :
	inc byte[len] 
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
	add dl , 1
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
