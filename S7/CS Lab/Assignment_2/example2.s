	.file	"example2.c"
	.text
	.globl	function
	.type	function, @function
function:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	movl	8(%ebp), %eax
	movl	%eax, -44(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	subl	$8, %esp
	pushl	-44(%ebp)
	leal	-28(%ebp), %eax
	pushl	%eax
	call	strcpy
	addl	$16, %esp
	nop
	movl	-12(%ebp), %eax
	xorl	%gs:20, %eax
	je	.L2
	call	__stack_chk_fail
.L2:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	function, .-function
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$276, %esp
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	movl	$0, -272(%ebp)
	jmp	.L4
.L5:
	leal	-268(%ebp), %edx
	movl	-272(%ebp), %eax
	addl	%edx, %eax
	movb	$65, (%eax)
	addl	$1, -272(%ebp)
.L4:
	cmpl	$254, -272(%ebp)
	jle	.L5
	subl	$12, %esp
	leal	-268(%ebp), %eax
	pushl	%eax
	call	function
	addl	$16, %esp
	nop
	movl	-12(%ebp), %eax
	xorl	%gs:20, %eax
	je	.L6
	call	__stack_chk_fail
.L6:
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
