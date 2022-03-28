.globl main

.text

main :
    li $v0, 4
    la $a0, psa
    syscall

    li $v0, 8
    la $a0, string_a
    syscall

    li $v0, 4
    la $a0, psb
    syscall

    li $v0, 8
    la $a0, string_b
    syscall

    la $a0, string_a
    la $a1, string_b 
    jal strcmp

    beqz $v1, Yes

No : 
    li $v0, 4
    la $a0, no 
    syscall
    j exit

Yes :
    li $v0, 4
    la $a0, yes
    syscall
    j exit

strcmp :
    li $v1, 1
    li $t0, 0
    li $t1, 0
    li $t2, 0
    move $t3, $a0
    move $t4, $a1
cmp_loop :
    lb $t1, 0($a0) 
    lb $t2, 0($a1)
    bne $t1, $t2 , exit_strcmp 
    beqz $t1, equal
    addi $a0, $a0, 1
    addi $a1, $a1, 1
    j cmp_loop
equal :
    li $v1, 0
exit_strcmp :
    jr $ra

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
    psa: .asciiz "Enter String 1 : "
    psb: .asciiz "Enter String 2 : "
    yes: .asciiz "EQUAL\n"
    no: .asciiz "NOT EQUAL\n"
    spc: .asciiz " "
    nl: .asciiz "\n"
    string_a: .space 256
    string_b: .space 256