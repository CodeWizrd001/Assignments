section .data
	pm : db "Enter m : "
	lm : equ $-pm
	pn : db "Enter n : "
	ln : equ $-pn
	parr1 : db "Enter Elements Of 1st Matrix : ",10
	larr : equ $-parr1
	parr2 : db "Enter Elements Of 2nd Matrix : ",10
	parrs : db "The Sum Of The Two Matrices Is : ",10
	larrs : equ $-parrs
	spc : db 32
	nl : db 10

section .bss
	t : resw 1
	a : resw 1
	b : resw 1
	n : resw 1
	m : resw 1
	beg : resw 1
	end : resw 1
	mid : resw 1
	arr1 : resw 100
	arr2 : resw 100
	arr3 : resw 100
	flag : resw 1
	temp : resw 1 
	count : resb 1
	prime : resw 1
	temp_ : resd 1
	temp__ : resd 1
	
section .text
global _start
_start :
	
	mov eax , 4
	mov ebx , 1
	mov ecx , pm
	mov edx , lm
	int 80h	
	
	call read 
	mov ax , word[temp]
	mov word[m] , ax

	mov eax , 4
	mov ebx , 1
	mov ecx , pn
	mov edx , ln
	int 80h 

	call read
	mov ax , word[temp]
	mov word[n] , ax

	mov eax , 4
	mov ebx , 1
	mov ecx , parr1
	mov edx , larr
	int 80h
	
	mov eax , arr1
	call readMatrix

	mov eax , 4
	mov ebx , 1
	mov ecx , parr2
	mov edx , larr
	int 80h

	mov eax , arr2
	call readMatrix	

	call sumMatrix

	mov eax , 4
	mov ebx , 1
	mov ecx , parrs
	mov edx , larrs
	int 80h

	mov eax , arr3
	call printMatrix
	
	call exit

; Read M x N Matrix
readMatrix :
	pusha
	mov edx , 0
pMLoop :
	cmp dx , word[m]
	je sRMat
	push edx
	push eax
	mov eax , edx
	mov edx , 0
	mov bx , word[n]
	mul bx
	mov edx, 0
	mov bx , 2
	mul bx
	mov edx , eax
	pop eax	
	add eax , edx 
	call readArray
	sub eax , edx
	pop edx
	inc edx
	jmp pMLoop 
sRMat :
	popa
	ret	

; Print M x N Matrix
printMatrix :
	pusha
	mov edx , 0
readMLoop :
	cmp dx , word[m]
	je sPMat
	push edx
	push eax
	mov eax , edx
	mov edx , 0 
	mov bx , word[n]
	mul bx 
	mov edx , 0
	mov bx , 2
	mul bx
	mov edx , eax
	pop eax
	add eax , edx
	call printArray
	sub eax , edx
	pop edx
	inc edx
	jmp readMLoop 
sPMat :
	popa
	ret

; Elementwise Sum Of Two Matrices
sumMatrix :
	pusha
	mov ebx , 0
	mov eax , arr1
	mov edx , arr2
	mov ecx , arr3
sumMatLoop :
	cmp bx , word[m]
	je sSMat
	pusha
	mov eax , ebx
	mov bx , 2
	mul bx
	mov bx , word[n]
	mul bx
	mov dword[temp_] , eax
	popa
	add eax , dword[temp_]
	add ecx , dword[temp_]
	add edx , dword[temp_]
	call sumArrays
	sub eax , dword[temp_]
	sub ecx , dword[temp_]
	sub edx , dword[temp_]
	inc ebx
	jmp sumMatLoop
sSMat :
	popa
	ret

; Element Wise Sum Of Two Arrays
sumArrays :
	pusha
	mov ebx , 0
sumsLoop :
	cmp bx , word[n]
	je sSArr
	push ecx
	mov cx , word[eax+2*ebx]
	add cx , word[edx+2*ebx]
	mov dword[temp__] , eax	
	mov ax , cx
	pop ecx
	mov word[ecx+2*ebx] , ax
	mov eax , dword[temp__] 
	inc ebx
	jmp sumsLoop 
sSArr :
	popa
	ret

; Read Array Of N Elements
readArray :
	pusha
	mov ebx , 0
readLoop :
	cmp bx , word[n] 
	je sRArr
	call read
	mov cx , word[temp] 
	mov word[eax+2*ebx] , cx
	inc ebx
	jmp readLoop
sRArr :
	popa
	ret

; Array Of N Elements
printArray :
	pusha 
	mov ebx , 0
printLoop :
	cmp bx , word[n]
	je sPArr
	mov cx , word[eax+2*ebx]
	mov word[temp] , cx
	call print
	inc ebx
	jmp printLoop
sPArr :
	call printnl
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
	call printsp
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
