section .data 
	nl : db 10
	spc : db 32
	prot : db "Enter A String : "
	lrot : equ $-prot
	pwod : db " Is a palindrome ",10
	lwod : equ $-pwod
	pnum : db " Is not a palindrome",10
	lnum : equ $-pnum
	
section .bss 
	string : resb 100
	nstring : resb 100
	count : resb 1
	pflag : resb 1
	temp : resw 1
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

	mov eax , string
	mov ebx , nstring

	movzx ecx , word[len]
	mov word[temp] , cx
	mov ecx , 0
	call Copy

	mov ecx , string
	movzx edx , word[len]
	call print_string

	call checkPal

	cmp byte[pflag] , 1
	je Pal
nPal :
	mov ecx , pnum 
	mov edx , lnum
	call print_string
	jmp exit
Pal :
	mov ecx , pwod
	mov edx , lwod
	call print_string
	jmp exit

checkPal :
	pusha
	mov byte[pflag] , 1
	mov ebx , 0
	dec ebx
chLoop :
	inc ebx
	cmp bx , word[len]
	je eCheck
	movzx ecx , byte[string+ebx]
	movzx edx , byte[nstring+ebx]
	cmp ecx , edx 
	jne np 
	jmp chLoop
np :
	inc byte[pflag]
eCheck :
	popa
	ret

Copy :
	pusha
	dec cx
copyLoop :
	inc cx
	dec word[temp]
	cmp cx , word[len]
	je eCopy
x : 
	push ecx
	movzx ecx , word[temp]
	movzx edx , byte[eax+ecx]
	pop ecx
	mov byte[ebx+ecx] , dl
;	dec word[temp]
	jmp copyLoop
eCopy :
	popa
	ret

count_all :
	pusha
	mov ebx , -1
c_loop :
	inc ebx 
	cmp bx , word[len]
	je eCount 
	mov cl , byte[eax+ebx]
	cmp cl , 91
	jg gA
	cmp cl , 65
	jl Num
	jmp cAlp
gA :
	cmp cl , 95
	jl cSpc
	cmp cl , 121
	jg cSpc
	jmp cAlp
Num :
	cmp cl , 48
	jl cSpc
	cmp cl , 58
	jge cSpc
	jmp cNum
cSpc :
	cmp cl , 32
	jne ccCont
	inc word[wod]
ccCont :
	inc word[sph]
	jmp c_loop
cNum :
	inc word[num]
	jmp c_loop
cAlp :
	inc word[alp]
	jmp c_loop
eCount :
	inc word[wod]
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
	mov byte[ebx+eax] , 0
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
	
