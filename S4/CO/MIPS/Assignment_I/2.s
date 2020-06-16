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

    # Read b
    li $v0, 5
    syscall
    move $s6, $v0

loop :
    bgt $s5, $s6, exit_loop 	# if $s5 > $s6
    move $a0, $s5
    jal prime_check
    beqz $v1, loop_cont
    # Print Number
    li $v0, 1
    move $a0, $s5
    syscall
    jal print_space
loop_cont :
    addi $s5, $s5 ,1 
    j loop 
exit_loop :
    j exit 

prime_check :
    li $v1, 0           # Prime Flag
    li $t0, 2           # i = 2
    blt	$a0, $t0, exit_prime_check
    div $a0, $t0        # N/2 
    mflo $t1            # t1 = N / 2
prime_check_loop :
    bgt $t0, $t1, prime
    div	$a0, $t0			# N / i
    mfhi $t3			    # $t3 = N % i
    beqz $t3 , exit_prime_check
    addi $t0, $t0, 1		# i += 1
    j prime_check_loop
prime :    
    li $v1, 1
exit_prime_check :
    addi $sp,$sp,16
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
    prompt_a: .asciiz "Enter Start : "
    prompt_b: .asciiz "Enter End : "
    spc: .asciiz " "
    nl: .asciiz "\n"