.globl main

.text

main :
    li $v0, 4
    la $a0, psa
    syscall

    li $v0, 8
    la $a0, string
    syscall

    li $v0, 4
    la $a0, psb
    syscall

    li $v0, 8
    la $a0, substring
    syscall

    la $a0, string
    la $a1, substring 
    jal checkSubstring

    li $t0, 1
    bgt	$v1, $t0, Yes

No : 
    li $v0, 4
    la $a0, no 
    syscall
    j exit

Yes :
    addi $sp, $sp, -4
    sw $a0, 0($sp)
    li $v0, 4
    la $a0, yes 
    syscall
    lw $a0, 0($sp)
    addi $sp, $sp, 4

    li $v0, 1
    la $a1, string
    sub $a0, $a0, $a1
    syscall
    jal print_nl
    j exit

checkSubstring :
    li $v1, 1
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    li $t3, 0
    li $t4, 0
    lb $t4, 0($a1)
checkLoop :
    lb $t3, 0($a0)
    beqz $t3, retCheck
    bne $t3, $t4, clCont
    move $a2, $a0 
    move $a3, $a1 
    jal modstrcmp
    beqz $v1, subs
clCont :
    addi $a0, $a0, 1
    j checkLoop
subs :
    move $v1, $a0
retCheck :
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

modstrcmp :
    addi $sp, $sp, -8
    li $v1, 1
    li $t0, 10
    li $t1, 0
    li $t2, 0
cmp_loop :
    lb $t1, 0($a2) 
    lb $t2, 0($a3)
    beq $t2, $t0, success
    bne $t1, $t2 , exit_strcmp 

    addi $a2, $a2, 1
    addi $a3, $a3, 1
    j cmp_loop
success :
    li $v1, 0
exit_strcmp :
    addi $sp, $sp, 8
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
    psa: .asciiz "Enter String : "
    psb: .asciiz "Enter Sub-String : "
    yes: .asciiz "Index of Substring : "
    no: .asciiz "NOT SUBSTRING\n"
    spc: .asciiz " "
    nl: .asciiz "\n"
    string: .space 2560
    substring: .space 256