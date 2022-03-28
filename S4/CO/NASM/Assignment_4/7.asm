section .data 
	nl : db 10
	spc : db 32
	prot : db "Enter A String : "
	lrot : equ $-prot
	pwod : db "Enter Character To Remove : "
	lwod : equ $-pwod
	pnum : db "Final String : "
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

	mov ecx , pwod
	mov edx , lwod
	call print_string

	mov eax , 3
	mov ebx , 1
	mov ecx , t
	mov edx , 1
	int 80h
	
	movzx ecx , word[len]
	mov word[temp] , cx
	mov ecx , 0

	call Copy

	mov ecx , pnum
	mov edx , lnum
	call print_string

	mov ecx , nstring
	movzx edx , word[len]
	call print_string
	call printnl
	
	jmp exit

Copy :
	pusha
	mov edx , 0
	dec edx 
	mov ebx , 0
copyLoop :
	inc edx
	cmp dx , word[len]
	je eCopy
clear1 :
	movzx ecx , byte[string+edx]
	cmp cl , byte[t]
	je copyLoop
clear2 :
	mov byte[nstring+ebx] , cl
	inc ebx
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
	
