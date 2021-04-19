# $t6 - i - before previous
# $t7 - j - previous
# $s7 - k - current
# $s5 - a
# $s6 - b

.globl main

.text

main :
    # Print Prompt a
    li $v0, 4
    la $a0, prompt_a
    syscall

    # Read a
    li $v0, 5
    syscall
    move $s5, $v0
    move $s6, $v0

    li $t7 , 10

    li $t6, 0               # Digit Count = 0

get_digits :
    beqz $s5 ,get_narc_sum

    div $s5,$t7
    mflo $s5
    mfhi $t3

    addi $t6, $t6, 1        # Digit Count += 1
    addi $sp, $sp, -4        # Push Digit 
    sw $t3, 0($sp)

    j get_digits

get_narc_sum :
    move $t5, $t6
    li $s0, 0
narcLoop :
    beqz $t5, exit_sum
    addi $t5, -1
    move $t4, $t6

    lw $t3, 0($sp)
    addi $sp, $sp, 4
    
    move $a0, $t3
    move $a1, $t6 
    jal power
    
    add $s0, $s0, $v1
    
    j narcLoop

exit_sum :
    beq $s6,$s0,pyes
    j pno

power : 
    li $v1, 1
    move $t4, $a1
powLoop :
    beqz $t4, retPower
    addi $t4, -1
    mult $v1, $a0
    mflo $v1
    j powLoop
retPower :
    jr $ra

pyes :
    li $v0, 4
    la $a0, yes
    syscall

    j exit

pno :
    li $v0, 4
    la $a0, no
    syscall

    j exit

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
    yes: .asciiz "YES\n"
    no: .asciiz "NO\n"
    spc: .asciiz " "
    nl: .asciiz "\n"