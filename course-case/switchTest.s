	.file	"switchTest.c"
	.text
	.globl	switcher
	.type	switcher, @function
switcher:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$1, -4(%rbp)
	cmpq	$10, -24(%rbp)
	ja	.L2
	movq	-24(%rbp), %rax
	leaq	0(,%rax,4), %rdx
	leaq	.L4(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L4(%rip), %rdx
	addq	%rdx, %rax
	notrack jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L4:
	.long	.L2-.L4
	.long	.L10-.L4
	.long	.L9-.L4
	.long	.L8-.L4
	.long	.L7-.L4
	.long	.L6-.L4
	.long	.L6-.L4
	.long	.L2-.L4
	.long	.L2-.L4
	.long	.L5-.L4
	.long	.L3-.L4
	.text
.L10:
	addl	$1, -4(%rbp)
	jmp	.L11
.L9:
	addl	$3, -4(%rbp)
	jmp	.L11
.L8:
	addl	$3, -4(%rbp)
	jmp	.L11
.L7:
	addl	$4, -4(%rbp)
	jmp	.L11
.L6:
	addl	$6, -4(%rbp)
	jmp	.L11
.L5:
	addl	$333, -4(%rbp)
	subq	$1, -24(%rbp)
	jmp	.L11
.L3:
	addl	$444, -4(%rbp)
	jmp	.L11
.L2:
	movl	$1233, -4(%rbp)
	nop
.L11:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	switcher, .-switcher
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
