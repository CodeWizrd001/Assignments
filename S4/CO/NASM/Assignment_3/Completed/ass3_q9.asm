section .data
	pm : db "Enter m : "
	lm : equ $-pm
	pn : db "Enter n : "
	ln : equ $-pn
	parr1 : db "Enter Elements Of 1st Matrix of M x N : ",10
	larr : equ $-parr1
	parr2 : db "Enter Elements Of 2nd Matrix of N x M : ",10
	parrs : db "The Product Of The Two Matrices Is : ",10
	larrs : equ $-parrs
	spc : db 32
	nl : db 10

section .bss
	t : resw 1
	a : resw 1
	b : resw 1
	n : resw 1
	m : resw 1
	i : resw 1
	j : resw 1
	k : resw 1
	ic : resw 1
	kc : resw 1
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

	call mulMatrix

	mov eax , 4
	mov ebx , 1
	mov ecx , parrs
	mov edx , larrs
	int 80h

	mov eax , arr3
	call printMatrix
	
	call exit

mulMatrix :
	pusha 
	mov word[i] , 0
	mov word[j] , 0
	mov word[k] , 0
mLoop :
	mov word[j] , 0
	mov word[k] , 0
	mov ax , word[i]
	cmp ax , word[m]
	je sMul
mLoop_ :
	mov word[k] , 0
	movzx eax , word[j]
	cmp ax , word[m]
	jne cM_
	inc word[i]
	jmp mLoop
cM_ :
mLoop__ :
	movzx eax , word[k]
	cmp ax , word[m]
	jne cM__
	inc word[j]
	jmp mLoop_
cM__ :
	mov ax , word[i]
	mov dx , 0
	mov bx , word[n]
	mul bx
	mov word[ic] , ax
	mov ax , word[k]
	mov dx , 0
	mul bx
	mov word[kc] , ax
	movzx edx , word[ic]
	add dx , word[k]
	mov ax , word[arr1+2*edx]
	movzx edx , word[kc]
	add dx , word[j]
	mov bx , word[arr2+2*edx]
	mov edx , 0
	mul bx
	movzx edx , word[ic]
	add dx , word[j]
	add word[arr3+2*edx] , ax
	inc word[k]
	jmp mLoop__
sMul :
	popa
	ret

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

; Transpose Of M x N Matrix
transposeMatrix :
	pusha
	mov eax , 0
	mov ebx , 0
	mov ecx , 0
	mov edx , 0
trLoop :
	cmp dx , word[m]
	je sTrM
	mov ebx , 0
trMLoop :
	mov eax , 0
	cmp bx , word[n]
	jne loopT
	inc edx
	jmp trLoop
loopT :
	mov ax , dx
	push edx
	push ebx
	mov edx , 0
	mov bx , word[n]
	mul bx
	pop ebx
	add eax , ebx
b1 :
	mov cx , word[arr1+2*eax]
	mov word[temp] , cx
	mov eax , ebx
	push ebx
	mov edx , 0
	mov bx , word[m]
	mul bx
	pop ebx
	pop edx
	add eax , edx
	mov word[arr2+2*eax] , cx
	inc ebx
	jmp trMLoop
sTrM :
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
