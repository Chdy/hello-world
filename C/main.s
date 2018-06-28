	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
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
	xorl	%eax, %eax
	movq	_pd(%rip), %rcx
	movq	%rcx, -8(%rbp)
	movq	_pf(%rip), %rcx
	movq	%rcx, -16(%rbp)
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z4swapRiS_
	.align	4, 0x90
__Z4swapRiS_:                           ## @_Z4swapRiS_
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
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rsi
	movl	(%rsi), %eax
	movl	%eax, -20(%rbp)
	movq	-16(%rbp), %rsi
	movl	(%rsi), %eax
	movq	-8(%rbp), %rsi
	movl	%eax, (%rsi)
	movl	-20(%rbp), %eax
	movq	-16(%rbp), %rsi
	movl	%eax, (%rsi)
	popq	%rbp
	retq
	.cfi_endproc

	.section	__DATA,__data
	.globl	_pd                     ## @pd
	.align	3
_pd:
	.quad	__Z4swapii

	.globl	_pf                     ## @pf
	.align	3
_pf:
	.quad	__Z4swapii


.subsections_via_symbols
