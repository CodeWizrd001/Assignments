section .data
	pn : db "Enter n : "
	ln : equ $-pn
	parr : db "Enter Array Elements : ",10
	larr : equ $-parr
	ps : db "Sorted Array : ",10
	ls : equ $-ps
	nl : db 10
	spc : db 32

section .bss
	t : resw 1
	a : resw 1
	n : resw 1
	x : resw 1
	min : resb 1
	beg : resw 1
	end : resw 1
	mid : resw 1
	key : resw 1
	arr : resw 100
	flag : resw 1
	temp : resw 1 
	count : resb 1

section .text
global _start
_start :
	
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
	mov ecx , parr
	mov edx , larr
	int 80h
	
	call readArray	

	mov eax , 4
	mov ebx , 1
	mov ecx , ps
	mov edx , ls
	int 80h

	call iSort

	call printArray
	call printnl
	
	call exit

; Insertion Sort
iSort :
	pusha
	mov eax , arr
	mov ebx , 0
mainLoop :
	cmp bx , word[n]
	je sSort
	mov cx , word[eax+2*ebx]
	mov word[key] , cx
	pusha
	mov edx , ebx
	dec ebx
	mov ecx , 0
sortLoop :
	cmp ebx , 0
	jl ssLoop
	mov cx , word[eax+2*ebx]
	cmp cx , word[key] 
	jle ssLoop
	mov cx , word[eax+2*ebx]
	inc ebx
	mov word[eax+2*ebx] , cx
	sub ebx , 2
	jmp sortLoop
ssLoop :
	inc ebx
	mov ecx , 0
	mov cx , word[key]
	mov word[eax+2*ebx] , cx
	popa
	inc ebx	
	jmp mainLoop
sSort :
	popa
	ret

; Function To Return MinIndex
minArr :
	pusha
	mov eax , arr 
	movzx edx , word[eax+2*ebx]
	mov word[min] , bx
minLoop :
	cmp bx , word[n] 
	je sMin
	cmp dx , word[eax+2*ebx]
	jle cMin
	mov dx , word[eax+2*ebx]
	mov word[min] , bx
cMin:
	inc ebx 
	jmp minLoop
sMin :
	popa
	ret
	
; Read Array Of N Elements
readArray :
	pusha
	mov eax , arr
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
	mov eax , arr 
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
