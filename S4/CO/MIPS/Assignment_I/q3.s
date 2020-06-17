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
    move $s6, $v0

    li $t7 , 10
    li $s0 , 0

get_cube_sum :
    beqz $s5 ,exit_loop

    div $s5,$t7
    mflo $s5
    mfhi $t5

    mult $t5, $t5
    mflo $t2

    mult $t2, $t5
    mflo $t2
    
    add	$s0, $s0, $t2		# $s0 = s0 +t2
    
    j get_cube_sum

exit_loop :
    beq $s6,$s0,pyes
    j pno

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