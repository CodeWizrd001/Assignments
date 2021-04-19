			section .text
global _start:
_start:

call read_num
movzx eax,word[num]
mov dword[row1],eax
mov dword[row],eax
call read_num
movzx eax,word[num]
mov dword[col1],eax
mov dword[col],eax
mov eax,a
call read_array
call read_num
movzx eax,word[num]
mov dword[row2],eax
mov dword[row],eax
call read_num
movzx eax,word[num]
mov dword[col2],eax
mov dword[col],eax
mov eax,b
call read_array
call find_array_sum
call print_array
mov eax,1
mov ebx,0
int 80h

			read_num:
pusha
mov word[num],0
		digit_read_loop:
mov eax,3
mov ebx,0
mov ecx,d
mov edx,1
int 80h
cmp byte[d],10
je end_digit_read_loop
sub byte[d],30h
mov ax,word[num]
mov bx,10
mul bx
movzx cx,byte[d]
add ax,cx
mov word[num],ax
jmp digit_read_loop
		end_digit_read_loop:
popa
ret


			print_num:
pusha
mov ax,word[num]
mov bx,10
mov byte[count],0
		digit_push_loop:
mov dx,0
div bx
push dx
inc byte[count]
cmp ax,0
jne digit_push_loop

		digit_print_loop:
pop dx
mov byte[d],dl
add byte[d],30h
mov eax,4
mov ebx,1
mov ecx,d
mov edx,1
int 80h
dec byte[count]
cmp byte[count],0
jne digit_print_loop
popa
ret

			find_ebx:
push eax 
mov eax,dword[r]
mov ebx,dword[col]
mul bx
add eax,dword[c]
mov ebx,eax
pop eax
ret



			read_array:
;mov eax,a
mov dword[r],0
		read_array_loop1:
mov dword[c],0
mov ebx,dword[r]
cmp ebx,dword[row]
jnl end_read_array_loop1
		read_array_loop2:
mov ebx,dword[c]
cmp ebx,dword[col]
jnl end_read_array_loop2
call read_num
mov cx,word[num]
call find_ebx
mov word[eax+2*ebx],cx
inc dword[c]
jmp read_array_loop2
		end_read_array_loop2:
inc dword[r]
jmp read_array_loop1
		end_read_array_loop1:
ret
  
			print_array:
pusha
mov eax,arr
mov dword[r],0
		print_array_loop1:
mov dword[c],0
mov ebx,dword[r]
cmp ebx,dword[row]
jnl end_print_array_loop1
		print_array_loop2:
mov ebx,dword[c]
cmp ebx,dword[col]
jnl end_print_array_loop2
call find_ebx
mov cx,word[eax+2*ebx]
mov word[num],cx
call print_num
inc dword[c]
pusha
mov eax,4
mov ebx,1
mov ecx,msg
mov edx,1
int 80h
popa
jmp print_array_loop2
		end_print_array_loop2:
inc dword[r]
pusha
mov eax,4
mov ebx,1
mov ecx,entr
mov edx,1
int 80h
popa
jmp print_array_loop1
		end_print_array_loop1:
popa
ret


			find_array_sum:
pusha
mov eax,a
mov edx,b
mov dword[r],0
		sum_array_loop1:
mov dword[c],0
mov ebx,dword[r]
cmp ebx,dword[row]
jnl end_sum_array_loop1
		sum_array_loop2:
mov ebx,dword[c]
cmp ebx,dword[col]
jnl end_sum_array_loop2
call find_ebx
c1 :
mov cx,word[eax+2*ebx]
c2 :
add cx,word[edx+2*ebx]
c3 :
push eax
c4 :
mov eax,arr
call find_ebx
mov word[eax+2*ebx],cx
pop eax
inc dword[c]
jmp sum_array_loop2
		end_sum_array_loop2:
inc dword[r]
jmp sum_array_loop1
		end_sum_array_loop1:
popa
ret




			section .data
msg:db ' '
entr:db 10

			section .bss
num:resw 1
size:resw 2
d:resb 1
count:resb 1
a:resw 20		
b:resw 20
arr:resw 20
freq:resb 1
prime_flag:resb 1
temp:resw 2
col1:resw 2
col2:resw 2
row1:resw 2
row2:resw 2
r:resw 2
c:resw 2
col:resw 2
row:resw 2
