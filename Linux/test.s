	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_all
	.align	4, 0x90
_all:                                   ## @all
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	leaq	-16(%rbp), %rcx
	movq	(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movq	%rcx, -24(%rbp)
	movq	-24(%rbp), %rcx
	movq	(%rax), %rax
	cmpq	-8(%rbp), %rax
	movq	%rcx, -32(%rbp)         ## 8-byte Spill
	jne	LBB0_2
## BB#1:
	movq	-32(%rbp), %rax         ## 8-byte Reload
	addq	$32, %rsp
	popq	%rbp
	retq
LBB0_2:
	callq	___stack_chk_fail
	.cfi_endproc

	.globl	_ca
	.align	4, 0x90
_ca:                                    ## @ca
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp3:
	.cfi_def_cfa_offset 16
Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp5:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	$3, -12(%rbp)
	movl	$23, -16(%rbp)
	movl	$3, -20(%rbp)
	movl	$5, -24(%rbp)
	movl	$6, -28(%rbp)
	movl	-12(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp6:
	.cfi_def_cfa_offset 16
Ltmp7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp8:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	callq	_all
	movl	$1, %edi
	movl	$2, %esi
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movl	$2, (%rax)
	movq	-32(%rbp), %rax
	movl	$1, 4(%rax)
	callq	_ca
	movl	$1, %esi
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	movl	%esi, %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc


.subsections_via_symbols
