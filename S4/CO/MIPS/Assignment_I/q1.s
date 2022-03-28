# $t6 - i - before previous
# $t7 - j - previous
# $s7 - k - current
# $s6 - N

.globl main

.text

main :
    li $t6, 0 
    li $t7, 1
    li $s7, 0

    li $v0, 4
    la $a0, text
    syscall

    # Getting user input
    li $v0, 5
    syscall

    move $s6, $v0   # N

loop :
    # If current < N jump to exit
    slt $s1,$s7,$s6
    beqz $s1,exit

    # Print number
    li $v0, 1
    move $a0, $s7
    syscall
    jal print_space

    move $t6, $t7           # i = j
    move $t7, $s7           # j = k
    add $s7,$t7,$t6         # k = i + j
    j loop

print_space :
    li $v0, 4
    la $a0, spc 
    syscall
    jr $ra 

print_nl : 
    li $v0, 4 
    la $a0, nl 
    syscall
    jr $ra

exit : 
    jal print_nl
    li $v0, 10
    syscall

.data
    text:  .asciiz "Enter end : "
    spc: .asciiz " "
    nl: .asciiz "\n"