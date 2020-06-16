# $t6 - i - before previous
# $t7 - j - previous
# $s7 - k - current
# $s5 - a
# $s6 - b

.globl main

.text

main :
    li $t6, 0 
    li $t7, 1
    li $s7, 0

    # Print Prompt a
    li $v0, 4
    la $a0, prompt_a
    syscall

    # Read a
    li $v0, 5
    syscall
    move $s5, $v0

    # Print Prompt b
    li $v0, 4
    la $a0, prompt_b
    syscall

    # Read a
    li $v0, 5
    syscall
    move $s6, $v0

loop :
    # If i < N jump to exit
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

prime_check :

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
    prompt_a: .asciiz "Enter a : "
    prompt_b: .asciiz "Enter b : "
    spc: .asciiz " "
    nl: .asciiz "\n"