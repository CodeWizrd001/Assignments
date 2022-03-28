section .data 
	nl : db 10
	spc : db 32
	prot : db "Enter n : "
	lrot : equ $-prot
	prom : db "Enter The Elements : ",10
	lrom : equ $-prom
	format_int : db "%d",0
	format_in : db "%lf",0
	format_out : db "%lf ",10
	zr : db 0 
	pmn : db "FSIN : "
	lmn : equ $-pmn
        pmdn : db "Approximated Sin : "
        lmdn : equ $-pmdn
        pvr : db "Difference : "
        lvr : equ $-pvr
        pst : db "Standard Deviation : "
        lst : equ $-pst
	six : dw 6
	five : dw 120

section .bss 
	string : resb 100
	float__ : resq 1
	float_ : resq 1
	count : resb 1
	temp : resw 1
	len : resw 1 
	alp : resw 1
	num : resw 1
	min : resw 1
	n : resw 1
	arr : resq 100
	sin : resq 100
	siin : resq 100
	diff : resq 100
	mean : resq 1
	nom : resq 1
	din : resq 1
	pis : resq 1
	pix : resq 1
	d5 : resq 1
	d3 : resq 1
	median : resq 1
	stdev : resq 1
	vari : resq 1
	t : resb 1 
	tsq : resq 1
	tsqsum : resq 1

section .text 
global main 
	extern scanf
	extern printf
main :
	mov ecx , prot 
	mov edx , lrot
	call print_string

	call read_int
	mov word[num] , ax

	mov ecx , prom
	mov edx , lrom
	call print_string
	call read_float_array
	call calcFsin
	
	call clearStack
	call calcSin
	call calcDiff

	mov ecx , pmn 
	mov edx , lmn
	call print_string
	call printnl
	mov eax , sin
	call print_float_array

	mov ecx , pmdn
	mov edx , lmdn
	call print_string
	call printnl
	mov eax , siin
	call print_float_array

	mov ecx , pvr
	mov edx , lvr
	call print_string
	call printnl
	mov eax , diff
	call print_float_array	

	jmp exit

calcDiff :
	pusha
	call clearStack
	mov eax , 0
dLoop :
	cmp word[num] , ax
	je sDiff
	fld qword[sin+8*eax]
	fsub qword[siin+8*eax]
	fabs
	fstp qword[diff+8*eax]
	inc eax 
	jmp dLoop
sDiff :
	popa
	ret

calcSin :
	pusha
	call clearStack
	mov eax , 0
calLoop :
	cmp word[num] , ax
	je scalS
	call clearStack
	fld qword[arr+8*eax]
	fmul qword[arr+8*eax]
	fmul qword[arr+8*eax]
	fst qword[d3]
	fmul qword[arr+8*eax]
	fmul qword[arr+8*eax]
	fstp qword[d5]
	fld qword[d5]
bef :
	fidiv word[five]
	fstp qword[d5]
	fld qword[d3]
	fidiv word[six]
	fstp qword[d3]
	fld qword[arr+8*eax]
	fsub qword[d3]
	fadd qword[d5]
	fstp qword[siin+8*eax]
	inc eax 
	jmp calLoop
scalS :
	popa
	ret

calcFsin :
	pusha
	call clearStack
	mov eax , 0
calfLoop :
	cmp word[num] , ax 
	je scalF
	fld qword[arr+8*eax]
	fsin
	fstp qword[sin+8*eax]
b2 : 	
	inc eax 
	jmp calfLoop
scalF :
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

findStd :
	pusha
	call clearStack
	fld qword[vari]
	fsqrt
	fstp qword[stdev]
	popa
	ret

findVar :
	pusha
	call clearStack
	mov eax , 0
	dec eax 
	fldz
	fst qword[tsq]
	fst qword[tsqsum]
fvLoop :
	call clearStack
	inc eax
	cmp ax , word[num]
	je fvCal
	fld qword[arr+8*eax]
	fmul ST0
	fstp qword[tsq]
	fld qword[tsqsum]
	fadd qword[tsq]
	fstp qword[tsqsum]
	jmp fvLoop
fvCal :
	call clearStack
	fld qword[tsqsum]
	fidiv word[num]
	fstp qword[tsqsum]
	fld qword[mean]
	fmul ST0
	fsub qword[tsqsum]
	fabs
	fstp qword[vari]	
sfvLoop :
	popa
	ret

findMean :
	pusha
	mov eax , 0
	dec eax 
	fldz
fmLoop :
	inc eax
	cmp ax , word[num]
	je sfMean
	fld qword[arr+8*eax]
	fadd ST1
	jmp fmLoop
sfMean :
	fidiv word[num]
	fstp qword[mean]
	call clearStack
	popa
	ret

findMedian :
	pusha
	movzx eax , word[num]
	mov edx , 0
	mov bx , 2
	div bx
	call clearStack
	fld qword[arr+8*eax]
	fstp qword[median]
b1 : 
	popa
	ret

sortFloat :
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
	ffree ST7
	ffree ST6
	ffree ST5
	ffree ST4
	ffree ST3
	ffree ST2
	ffree ST1
	ffree ST0
	fld qword[arr+8*ebx]
	fld qword[arr+8*(ebx-1)]
bcomp :
	fcomi ST1
	jb jCont 
swap :
	fstp qword[arr+8*ebx]
	fstp qword[arr+8*(ebx-1)]
	jmp jLoop
jCont :
	fstp qword[arr+8*(ebx-1)]
	fstp qword[arr+8*ebx]
	jmp jLoop
sSort :
	popa
	ret

print_float_array :
	pusha
	mov ebx , 0
	dec ebx
pfLoop :
	inc ebx
	cmp bx , word[num]
	je ePf
	fld qword[eax+8*ebx]
	call print_float
	jmp pfLoop
ePf :
	call printnl
	popa
	ret

read_float_array :
	pusha
	mov eax , arr
	mov ebx , 0
	dec ebx
rfLoop :
	inc ebx
	cmp bx , word[num]
	je eRf
	call read_float
	fst qword[arr+8*ebx]
	jmp rfLoop	
eRf :
	popa
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
	
