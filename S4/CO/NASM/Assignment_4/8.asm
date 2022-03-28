section .data 
	nl : db 10
	spc : db 32
	prot : db "Enter A String : "
	lrot : equ $-prot
	pwod : db "New String : "
	lwod : equ $-pwod
	pnum : db "Numbers : "
	lnum : equ $-pnum
	palp : db "Alphabets : "
	lalp : equ $-palp
	pspc : db "Special Characters : "
	lspc : equ $-pspc	
	
section .bss 
	string : resb 1000
	newstring : resb 1000
	wrd : resb 100
	count : resb 1
	temp : resw 1
	nlen : resw 1
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
	mov eax , string
	call read_string
	mov word[nlen] , 0
	call remDuplicates

	mov ecx , pwod
	mov edx , lwod
	call print_string

	mov ecx , newstring
	movzx edx , word[nlen]
	call print_string	
	call printnl
b1 :
	jmp exit

checkWord :
	pusha	
	mov ecx , 0
	mov eax , 0
check_ :
	cmp ax , word[nlen]
	je AddWord
	push eax
	mov ecx , 0
chLoop :
	cmp ax , word[nlen]
	je AddWord_
	cmp ecx , ebx
	je cRet_
	mov dl , byte[newstring+eax]
	cmp dl , byte[wrd+ecx]
	je checkCont
	pop eax
	inc eax 
	jmp check_
checkCont :
	inc eax
	inc ecx
	jmp chLoop
AddWord_ :
	pop eax
AddWord :
	mov eax , 0
	mov edx , 0
addLoop :
	movzx ecx , word[nlen]
	cmp eax , ebx
	je cRet
	mov dl , byte[wrd+eax]
	mov byte[newstring+ecx] , dl
	inc ecx 
	inc eax
	inc word[nlen]
	jmp addLoop
cRet_ :
	pop ebx
cRet :
	;mov byte[newstring+ebx] , 32
	;inc word[nlen]
	popa
	mov ebx , 0
	ret

remDuplicates :
	pusha
	mov eax , 0
	mov ebx , 0
getWords :
	cmp ax , word[len]
	jg endRem
	mov dl , byte[string+eax]
	mov byte[wrd+ebx] , dl
	inc eax 
	inc ebx
	cmp dl , 32
	je addL
	mov dl , byte[wrd+ebx-1]
	cmp dl , 0
	je addL
	mov dl , byte[wrd+ebx-1]
	cmp dl , 10
	je addL
	jmp addL_
addL :
	;pusha
	;mov edx , ebx
	;mov ecx , wrd
	;call print_string
	;call printnl
	;popa	
	call checkWord
addL_ :
	jmp getWords
endRem :
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
	
