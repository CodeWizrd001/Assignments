section .data 
	nl : db 10
	spc : db 32
	prot : db "Enter n : "
	lrot : equ $-prot
	prom : db "Enter The Numbers : ",10
	lrom : equ $-prom
	format_int : db "%d",0
	format_in : db "%lf",0
	format_out : db "%lf",10
	pzr : db 0
	pfsq : db "FSQRT : ",0
	lfsq : equ $-pfsq
	psq : db "Approximate Square : ",0
	lsq : equ $-psq
	pdif : db "Difference : ",0
	ldif : equ $-pdif	
	iooo : dw 1000
	

section .bss 
	string : resb 100
	float__ : resq 1
	float_ : resq 1
	sqrt : resq 1
	sqt : resq 1
	diff : resq 1
	count : resb 1
	temp : resw 1
	len : resw 1 
	alp : resw 1
	num : resw 1
	arr : resq 100
	t : resb 1 

section .text 
global main 
	extern scanf
	extern printf
main :
	mov ecx , prot 
	mov edx , lrot
	call print_string

	call read_float
	fst qword[float__]
	fld1
	fidiv word[iooo]
	fst qword[float_]
	
	call findRoot
	call clearStack

	mov ecx , psq
	mov edx , lsq
	call print_string
	fld qword[sqrt]
	call print_float

	call clearStack
	fld qword[float__]
	fsqrt
	fst qword[sqt]

	mov ecx , pfsq 
	mov edx , lfsq
	call print_string
	call print_float

	fld qword[sqrt]

	fsub ST1
	fabs
	fst qword[diff]
	call clearStack
	fld qword[diff]

	mov ecx , pdif
	mov edx , ldif 
	call print_string
	call print_float
b1 :
	jmp exit 

findRoot :
	pusha
	fldz
	fstp qword[sqrt]
sqLoop :
	call clearStack	
	fld qword[sqrt]
	fadd qword[float_]
	fst qword[sqrt]	
	fmul ST0
	fld qword[float__]
	fcomi ST1
check :
	jb efRoot
	jmp sqLoop	
efRoot :	
	call clearStack
	fld qword[sqrt]
	fsub qword[float_]
	fstp qword[sqrt]
	popa
	ret

clearStack :
	ffree ST0
	ffree ST1
	ffree ST2
	ffree ST3
	ffree ST4
	ffree ST5
	ffree ST6
	ffree ST7
	ret

read_int :
	push ebp
	mov ebp , esp
	sub esp , 2
	lea eax , [esp]
	push eax 
	push format_int
	call scanf
	mov ax , word[ebp-2]
	mov esp , ebp
	pop ebp
	ret

read_float :
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

print_float :
	pusha
	push ebp
	mov ebp , esp
	sub esp , 8
	fst qword[ebp-8]
	push format_out
	call printf
	mov esp , ebp
	pop ebp
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
	
