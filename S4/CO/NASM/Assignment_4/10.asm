section .data 
	nl : db 10
	spc : db 32
	prot : db "Enter n : "
	lrot : equ $-prot
	pwod : db "Enter Strings : "
	lwod : equ $-pwod
	pnum : db "Sorted : "
	lnum : equ $-pnum
	palp : db "Alphabets : "
	lalp : equ $-palp
	pspc : db "Special Characters : "
	lspc : equ $-pspc	
	
section .bss 
	string : resb 5000
	tsta : resb 100
	tstb : resb 100
	count : resb 1
	flag : resb 1
	temp : resw 1
	nlen : resw 100
	len : resw 1
	alp : resw 1
	num : resw 1
	sph : resw 1
	wod : resw 1
	t : resb 1 

section .text 
global _start 
_start :
	mov ecx , prot 
	mov edx , lrot
	call print_string
	call read
	mov ax , word[temp] 
	mov word[num] , ax
	mov word[wod] , ax
	
	mov ecx , pwod
	mov edx , lwod
	call print_string
	call printnl

	call read_n_strings

	mov ecx , pnum
	mov edx , lnum 
	call print_string
	call printnl
	call sortString
	call print_n_strings

b1 :
	jmp exit

strcmp :
	mov byte[flag] , 0
	pusha
comLoop :
	mov al , byte[ecx]
	mov bl , byte[edx]
	add byte[flag] , al
	sub byte[flag] , bl
	cmp byte[flag] , 0
	jne cmRet 
	inc ecx 
	inc edx 
	jmp comLoop
cmRet :
	popa
	ret	

sortString :
        pusha
        mov eax , 0
        dec eax
        mov ebx , 0
iLoop :
        inc eax
        cmp ax , word[num]
        je sSort
        mov ebx , 0
jLoop :
        inc ebx
        cmp bx , word[num]
        je iLoop
	push eax 
	push ebx
	mov eax , ebx
	mov ebx , 50
	mov edx , 0
	mul bx
	mov edx , string
	add edx , eax
	mov ecx , edx
	sub ecx , 50
	pop ebx 
	pop eax
	call strcmp
	cmp byte[flag] , 0
	jle jCont
swap :
	push ecx
	mov esi , edx
	mov edi , tsta
	mov ecx , 50
	rep movsb
	pop ecx
	push ecx
	mov esi , ecx
	mov edi , edx
	mov ecx , 50
	rep movsb
	pop ecx
	push ecx
	mov esi , tsta
	mov edi , ecx
	mov ecx , 50
	rep movsb
	pop ecx
jCont :
	jmp jLoop 
sSort :
        popa
        ret

read_n_strings :
	pusha
	mov eax , string
	mov ecx , 0
	mov ebx , 50
rnsLoop :
	cmp cx , word[num]
	je ennRead
	call read_string
	mov dx , word[len]
	mov word[nlen+2*ecx] , dx
	inc ecx
	add eax , ebx
	jmp rnsLoop
ennRead :
	popa
	ret

print_n_strings :
	pusha
	mov ecx , string
	mov ebx , 0
pnsLoop :
	cmp bx , word[num]
	je ennPrint
	push ecx
	movzx edx , word[nlen+2*ebx]
ceck :
	call print_string
	call printnl
	pop ecx
	add ecx , 50
	inc ebx
	jmp pnsLoop 
ennPrint :
	popa
	ret

; Multidigit Read Function
read :
        pusha
        mov word[temp] , 0
readDigs :
        mov eax , 3
        mov ebx , 0
        mov ecx , t
        mov edx , 1
        int 80h

        cmp word[t] , 10
        je sRead
        cmp word[t] , 32
        je sRead
        sub word[t] , 30h
        mov dx , 0
        mov ax , word[temp]
        mov bx , 10
        mul bx
        add ax , word[t]
        mov word[temp] , ax
        jmp readDigs
sRead :
        popa
        ret

; Multidigit Print Function
print :
        pusha
        mov byte[count] , 0
        cmp word[temp] , 0
        je printZero
splitDigs :
        cmp word[temp] , 0 
        je printDigs
        mov edx , 0 
        mov ax , word[temp]
        mov bx , 10
        div bx
        push edx
        mov word[temp] , ax
        inc byte[count]
        jmp splitDigs
printDigs :
        cmp byte[count] , 0
        je sPrint
        pop edx
        mov word[t] , dx
        add word[t] , 30h
        mov eax , 4
        mov ebx , 1
        mov ecx , t
        mov edx , 1
        int 80h
        dec byte[count]
        jmp printDigs
printZero :
        add word[temp] , 30h
        mov eax , 4
        mov ebx , 1
        mov ecx , temp
        mov edx , 1
        int 80h
sPrint :
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
	mov ebx , 0
rsLoop :
	push eax 
	push ebx
	mov eax , 3
	mov ebx , 0
	mov ecx , t
	mov edx , 1
	int 80h
	pop ebx
	pop eax 	

	cmp byte[t] , 10
	je eReads  
	mov cl , byte[t] 
	mov byte[eax+ebx] , cl 
	inc ebx
	jmp rsLoop
eReads :
	mov byte[ebx+eax] , 32
	mov byte[ebx+eax+1] , 0
	mov word[len] , bx
	popa
	ret

printnl :
	pusha
	mov eax , 4
	mov ebx , 1
	mov ecx , nl 
	mov edx , 1
	int 80h
	popa
	ret

printsp :
	pusha
	mov eax , 4
	mov ebx , 1
	mov ecx , spc
	mov edx , 1
	int 80h
	popa
	ret 

exit :
	mov eax , 1
	mov ebx , 0
	int 80h 
	
