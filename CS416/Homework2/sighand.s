	.file	"sighand.c"
.globl time
	.bss
	.align 4
	.type	time, @object
	.size	time, 4
time:
	.zero	4
	.comm	start,16,16
	.comm	end,16,16
.globl excute
	.align 4
	.type	excute, @object
	.size	excute, 4
excute:
	.zero	4
	.section	.rodata
	.align 8
.LC0:
	.string	"total time %d, run %d\n, average time %f\n"
	.text
.globl output
	.type	output, @function
output:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	time(%rip), %eax
	cvtsi2sd	%eax, %xmm0
	movsd	%xmm0, -24(%rbp)
	movl	excute(%rip), %eax
	cvtsi2sd	%eax, %xmm0
	movsd	%xmm0, -16(%rbp)
	movsd	-24(%rbp), %xmm0
	divsd	-16(%rbp), %xmm0
	movsd	%xmm0, -8(%rbp)
	movl	excute(%rip), %edx
	movl	time(%rip), %ecx
	movl	$.LC0, %eax
	movsd	-8(%rbp), %xmm0
	movl	%ecx, %esi
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	output, .-output
.globl sig_handler
	.type	sig_handler, @function
sig_handler:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$2, -4(%rbp)
	jne	.L4
	movl	excute(%rip), %eax
	addl	$1, %eax
	movl	%eax, excute(%rip)
.L4:
	cmpl	$20, -4(%rbp)
	jne	.L6
	movl	$0, %eax
	call	output
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	sig_handler, .-sig_handler
	.section	.rodata
.LC1:
	.string	"\n\ncan't catch SIGINT"
.LC2:
	.string	"\n\ncan't catch SIGTSTP"
	.text
.globl main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	call	getpid
	movl	%eax, -24(%rbp)
	movl	$sig_handler, %esi
	movl	$2, %edi
	call	signal
	cmpq	$-1, %rax
	jne	.L8
	movl	$.LC1, %edi
	call	puts
.L8:
	movl	$sig_handler, %esi
	movl	$20, %edi
	call	signal
	cmpq	$-1, %rax
	jne	.L9
	movl	$.LC2, %edi
	call	puts
.L9:
	movl	$0, %esi
	movl	$start, %edi
	call	gettimeofday
	movl	$0, -20(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L10
.L11:
	movl	-24(%rbp), %eax
	movl	$2, %esi
	movl	%eax, %edi
	call	kill
	addl	$1, -20(%rbp)
.L10:
	cmpl	$99, -20(%rbp)
	jle	.L11
	movq	end(%rip), %rax
	imull	$1000000, %eax, %edx
	movq	end+8(%rip), %rax
	leal	(%rdx,%rax), %ecx
	movq	start(%rip), %rax
	imull	$-1000000, %eax, %edx
	movq	start+8(%rip), %rax
	movl	%edx, %ebx
	subl	%eax, %ebx
	movl	%ebx, %eax
	leal	(%rcx,%rax), %eax
	movl	%eax, time(%rip)
	movl	-24(%rbp), %eax
	movl	$20, %esi
	movl	%eax, %edi
	call	kill
	movl	$0, %esi
	movl	$end, %edi
	call	gettimeofday
	movl	$0, %eax
	addq	$24, %rsp
	popq	%rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-4)"
	.section	.note.GNU-stack,"",@progbits
