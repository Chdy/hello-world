	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	__ZN10Sales_itempLERKS_ ## -- Begin function _ZN10Sales_itempLERKS_
	.p2align	4, 0x90
__ZN10Sales_itempLERKS_:                ## @_ZN10Sales_itempLERKS_
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rsi
	movq	-16(%rbp), %rdi
	movl	24(%rdi), %eax
	addl	24(%rsi), %eax
	movl	%eax, 24(%rsi)
	movq	-16(%rbp), %rdi
	movsd	32(%rdi), %xmm0         ## xmm0 = mem[0],zero
	addsd	32(%rsi), %xmm0
	movsd	%xmm0, 32(%rsi)
	movq	%rsi, %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZplRK10Sales_itemS1_  ## -- Begin function _ZplRK10Sales_itemS1_
	.p2align	4, 0x90
__ZplRK10Sales_itemS1_:                 ## @_ZplRK10Sales_itemS1_
Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception0
## BB#0:
	pushq	%rbp
Lcfi3:
	.cfi_def_cfa_offset 16
Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi5:
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	movq	%rdi, %rax
	movq	%rsi, -8(%rbp)
	movq	%rdx, -16(%rbp)
	movb	$0, -17(%rbp)
	movq	-8(%rbp), %rsi
	movq	%rdi, -48(%rbp)         ## 8-byte Spill
	movq	%rax, -56(%rbp)         ## 8-byte Spill
	callq	__ZN10Sales_itemC1ERKS_
	movq	-16(%rbp), %rsi
Ltmp0:
	movq	-48(%rbp), %rdi         ## 8-byte Reload
	callq	__ZN10Sales_itempLERKS_
Ltmp1:
	movq	%rax, -64(%rbp)         ## 8-byte Spill
	jmp	LBB1_1
LBB1_1:
	movb	$1, -17(%rbp)
	testb	$1, -17(%rbp)
	jne	LBB1_4
	jmp	LBB1_3
LBB1_2:
Ltmp2:
	movl	%edx, %ecx
	movq	%rax, -32(%rbp)
	movl	%ecx, -36(%rbp)
Ltmp3:
	movq	-48(%rbp), %rdi         ## 8-byte Reload
	callq	__ZN10Sales_itemD1Ev
Ltmp4:
	jmp	LBB1_5
LBB1_3:
	movq	-48(%rbp), %rdi         ## 8-byte Reload
	callq	__ZN10Sales_itemD1Ev
LBB1_4:
	movq	-56(%rbp), %rax         ## 8-byte Reload
	addq	$80, %rsp
	popq	%rbp
	retq
LBB1_5:
	jmp	LBB1_6
LBB1_6:
	movq	-32(%rbp), %rdi
	callq	__Unwind_Resume
LBB1_7:
Ltmp5:
	movl	%edx, %ecx
	movq	%rax, %rdi
	movl	%ecx, -68(%rbp)         ## 4-byte Spill
	callq	___clang_call_terminate
Lfunc_end0:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table1:
Lexception0:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.asciz	"\274"                  ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.byte	52                      ## Call site table length
Lset0 = Lfunc_begin0-Lfunc_begin0       ## >> Call Site 1 <<
	.long	Lset0
Lset1 = Ltmp0-Lfunc_begin0              ##   Call between Lfunc_begin0 and Ltmp0
	.long	Lset1
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset2 = Ltmp0-Lfunc_begin0              ## >> Call Site 2 <<
	.long	Lset2
Lset3 = Ltmp1-Ltmp0                     ##   Call between Ltmp0 and Ltmp1
	.long	Lset3
Lset4 = Ltmp2-Lfunc_begin0              ##     jumps to Ltmp2
	.long	Lset4
	.byte	0                       ##   On action: cleanup
Lset5 = Ltmp3-Lfunc_begin0              ## >> Call Site 3 <<
	.long	Lset5
Lset6 = Ltmp4-Ltmp3                     ##   Call between Ltmp3 and Ltmp4
	.long	Lset6
Lset7 = Ltmp5-Lfunc_begin0              ##     jumps to Ltmp5
	.long	Lset7
	.byte	1                       ##   On action: 1
Lset8 = Ltmp4-Lfunc_begin0              ## >> Call Site 4 <<
	.long	Lset8
Lset9 = Lfunc_end0-Ltmp4                ##   Call between Ltmp4 and Lfunc_end0
	.long	Lset9
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__ZN10Sales_itemC1ERKS_ ## -- Begin function _ZN10Sales_itemC1ERKS_
	.weak_def_can_be_hidden	__ZN10Sales_itemC1ERKS_
	.p2align	4, 0x90
__ZN10Sales_itemC1ERKS_:                ## @_ZN10Sales_itemC1ERKS_
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi6:
	.cfi_def_cfa_offset 16
Lcfi7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi8:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	callq	__ZN10Sales_itemC2ERKS_
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN10Sales_itemD1Ev    ## -- Begin function _ZN10Sales_itemD1Ev
	.weak_def_can_be_hidden	__ZN10Sales_itemD1Ev
	.p2align	4, 0x90
__ZN10Sales_itemD1Ev:                   ## @_ZN10Sales_itemD1Ev
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi9:
	.cfi_def_cfa_offset 16
Lcfi10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi11:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	__ZN10Sales_itemD2Ev
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.private_extern	___clang_call_terminate ## -- Begin function __clang_call_terminate
	.globl	___clang_call_terminate
	.weak_definition	___clang_call_terminate
	.p2align	4, 0x90
___clang_call_terminate:                ## @__clang_call_terminate
## BB#0:
	pushq	%rax
	callq	___cxa_begin_catch
	movq	%rax, (%rsp)            ## 8-byte Spill
	callq	__ZSt9terminatev
                                        ## -- End function
	.globl	__ZrsRNSt3__113basic_istreamIcNS_11char_traitsIcEEEER10Sales_item ## -- Begin function _ZrsRNSt3__113basic_istreamIcNS_11char_traitsIcEEEER10Sales_item
	.p2align	4, 0x90
__ZrsRNSt3__113basic_istreamIcNS_11char_traitsIcEEEER10Sales_item: ## @_ZrsRNSt3__113basic_istreamIcNS_11char_traitsIcEEEER10Sales_item
Lfunc_begin1:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception1
## BB#0:
	pushq	%rbp
Lcfi12:
	.cfi_def_cfa_offset 16
Lcfi13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi14:
	.cfi_def_cfa_register %rbp
	subq	$224, %rsp
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	-88(%rbp), %rdi
	movq	-96(%rbp), %rsi
	callq	__ZNSt3__1rsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_istreamIT_T0_EES9_RNS_12basic_stringIS6_S7_T1_EE
	movq	-96(%rbp), %rsi
	addq	$24, %rsi
	movq	%rax, %rdi
	callq	__ZNSt3__113basic_istreamIcNS_11char_traitsIcEEErsERj
	leaq	-104(%rbp), %rsi
	movq	%rax, %rdi
	callq	__ZNSt3__113basic_istreamIcNS_11char_traitsIcEEErsERd
	movq	-88(%rbp), %rsi
	movq	(%rsi), %rdi
	movq	-24(%rdi), %rdi
	addq	%rdi, %rsi
	movq	%rsi, -72(%rbp)
	movq	-72(%rbp), %rsi
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rsi
	movq	%rsi, -56(%rbp)
	movq	-56(%rbp), %rsi
	movl	32(%rsi), %ecx
	andl	$5, %ecx
	cmpl	$0, %ecx
	movq	%rax, -168(%rbp)        ## 8-byte Spill
	jne	LBB5_2
## BB#1:
	movq	__ZNSt3__112__cxx03_bool12__true_valueEv@GOTPCREL(%rip), %rax
	xorl	%ecx, %ecx
	movl	%ecx, %edx
	movq	%rax, -176(%rbp)        ## 8-byte Spill
	movq	%rdx, -184(%rbp)        ## 8-byte Spill
	jmp	LBB5_3
LBB5_2:
	leaq	-40(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	$-1, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rcx
	movq	%rax, -8(%rbp)
	movq	%rcx, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	movq	-40(%rbp), %rax
	movq	%rax, -80(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, -48(%rbp)
	xorl	%edx, %edx
	movl	%edx, %eax
	movq	%rax, %rcx
	movq	%rcx, -176(%rbp)        ## 8-byte Spill
	movq	%rax, -184(%rbp)        ## 8-byte Spill
	jmp	LBB5_3
LBB5_3:
	movq	-184(%rbp), %rax        ## 8-byte Reload
	movq	-176(%rbp), %rcx        ## 8-byte Reload
	cmpq	$0, %rcx
	movq	%rax, -192(%rbp)        ## 8-byte Spill
	je	LBB5_5
## BB#4:
	movq	-96(%rbp), %rax
	movl	24(%rax), %ecx
	movl	%ecx, %eax
	cvtsi2sdq	%rax, %xmm0
	mulsd	-104(%rbp), %xmm0
	movq	-96(%rbp), %rax
	movsd	%xmm0, 32(%rax)
	jmp	LBB5_9
LBB5_5:
	xorps	%xmm0, %xmm0
	movaps	%xmm0, -128(%rbp)
	movaps	%xmm0, -144(%rbp)
	movq	$0, -112(%rbp)
	leaq	-144(%rbp), %rax
	movq	%rax, %rdi
	movq	%rax, -200(%rbp)        ## 8-byte Spill
	callq	__ZN10Sales_itemC1Ev
	movq	-96(%rbp), %rdi
Ltmp6:
	movq	-200(%rbp), %rsi        ## 8-byte Reload
	callq	__ZN10Sales_itemaSERKS_
Ltmp7:
	movq	%rax, -208(%rbp)        ## 8-byte Spill
	jmp	LBB5_6
LBB5_6:
	leaq	-144(%rbp), %rdi
	callq	__ZN10Sales_itemD1Ev
	jmp	LBB5_9
LBB5_7:
Ltmp8:
	movl	%edx, %ecx
	movq	%rax, -152(%rbp)
	movl	%ecx, -156(%rbp)
Ltmp9:
	leaq	-144(%rbp), %rdi
	callq	__ZN10Sales_itemD1Ev
Ltmp10:
	jmp	LBB5_8
LBB5_8:
	jmp	LBB5_10
LBB5_9:
	movq	-88(%rbp), %rax
	addq	$224, %rsp
	popq	%rbp
	retq
LBB5_10:
	movq	-152(%rbp), %rdi
	callq	__Unwind_Resume
LBB5_11:
Ltmp11:
	movl	%edx, %ecx
	movq	%rax, %rdi
	movl	%ecx, -212(%rbp)        ## 4-byte Spill
	callq	___clang_call_terminate
Lfunc_end1:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table5:
Lexception1:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.byte	73                      ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.byte	65                      ## Call site table length
Lset10 = Lfunc_begin1-Lfunc_begin1      ## >> Call Site 1 <<
	.long	Lset10
Lset11 = Ltmp6-Lfunc_begin1             ##   Call between Lfunc_begin1 and Ltmp6
	.long	Lset11
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset12 = Ltmp6-Lfunc_begin1             ## >> Call Site 2 <<
	.long	Lset12
Lset13 = Ltmp7-Ltmp6                    ##   Call between Ltmp6 and Ltmp7
	.long	Lset13
Lset14 = Ltmp8-Lfunc_begin1             ##     jumps to Ltmp8
	.long	Lset14
	.byte	0                       ##   On action: cleanup
Lset15 = Ltmp7-Lfunc_begin1             ## >> Call Site 3 <<
	.long	Lset15
Lset16 = Ltmp9-Ltmp7                    ##   Call between Ltmp7 and Ltmp9
	.long	Lset16
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset17 = Ltmp9-Lfunc_begin1             ## >> Call Site 4 <<
	.long	Lset17
Lset18 = Ltmp10-Ltmp9                   ##   Call between Ltmp9 and Ltmp10
	.long	Lset18
Lset19 = Ltmp11-Lfunc_begin1            ##     jumps to Ltmp11
	.long	Lset19
	.byte	1                       ##   On action: 1
Lset20 = Ltmp10-Lfunc_begin1            ## >> Call Site 5 <<
	.long	Lset20
Lset21 = Lfunc_end1-Ltmp10              ##   Call between Ltmp10 and Lfunc_end1
	.long	Lset21
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__ZNSt3__1rsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_istreamIT_T0_EES9_RNS_12basic_stringIS6_S7_T1_EE ## -- Begin function _ZNSt3__1rsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_istreamIT_T0_EES9_RNS_12basic_stringIS6_S7_T1_EE
	.weak_definition	__ZNSt3__1rsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_istreamIT_T0_EES9_RNS_12basic_stringIS6_S7_T1_EE
	.p2align	4, 0x90
__ZNSt3__1rsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_istreamIT_T0_EES9_RNS_12basic_stringIS6_S7_T1_EE: ## @_ZNSt3__1rsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_istreamIT_T0_EES9_RNS_12basic_stringIS6_S7_T1_EE
Lfunc_begin2:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception2
## BB#0:
	pushq	%rbp
Lcfi15:
	.cfi_def_cfa_offset 16
Lcfi16:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi17:
	.cfi_def_cfa_register %rbp
	subq	$688, %rsp              ## imm = 0x2B0
	movq	%rdi, -488(%rbp)
	movq	%rsi, -496(%rbp)
	movq	-488(%rbp), %rsi
Ltmp12:
	leaq	-504(%rbp), %rdi
	xorl	%edx, %edx
	callq	__ZNSt3__113basic_istreamIcNS_11char_traitsIcEEE6sentryC1ERS3_b
Ltmp13:
	jmp	LBB6_1
LBB6_1:
	leaq	-504(%rbp), %rax
	movq	%rax, -480(%rbp)
	movq	-480(%rbp), %rax
	movb	(%rax), %cl
	movb	%cl, -562(%rbp)         ## 1-byte Spill
## BB#2:
	movb	-562(%rbp), %al         ## 1-byte Reload
	testb	$1, %al
	jne	LBB6_3
	jmp	LBB6_51
LBB6_3:
	movq	-496(%rbp), %rax
	movq	%rax, -456(%rbp)
	movq	-456(%rbp), %rax
	movq	%rax, -448(%rbp)
	movq	%rax, -408(%rbp)
	movq	-408(%rbp), %rcx
	movq	%rcx, -400(%rbp)
	movq	-400(%rbp), %rcx
	movq	%rcx, -392(%rbp)
	movq	-392(%rbp), %rcx
	movzbl	(%rcx), %edx
	movl	%edx, %ecx
	andq	$1, %rcx
	cmpq	$0, %rcx
	movq	%rax, -576(%rbp)        ## 8-byte Spill
	je	LBB6_5
## BB#4:
	leaq	-469(%rbp), %rsi
	movq	-576(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -312(%rbp)
	movq	-312(%rbp), %rcx
	movq	%rcx, -304(%rbp)
	movq	-304(%rbp), %rcx
	movq	%rcx, -296(%rbp)
	movq	-296(%rbp), %rcx
	movq	16(%rcx), %rdi
	movb	$0, -469(%rbp)
	callq	__ZNSt3__111char_traitsIcE6assignERcRKc
	movq	-576(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -336(%rbp)
	movq	$0, -344(%rbp)
	movq	-336(%rbp), %rcx
	movq	-344(%rbp), %rsi
	movq	%rcx, -328(%rbp)
	movq	-328(%rbp), %rcx
	movq	%rcx, -320(%rbp)
	movq	-320(%rbp), %rcx
	movq	%rsi, 8(%rcx)
	jmp	LBB6_6
LBB6_5:
	leaq	-470(%rbp), %rsi
	movq	-576(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -384(%rbp)
	movq	-384(%rbp), %rcx
	movq	%rcx, -376(%rbp)
	movq	-376(%rbp), %rcx
	movq	%rcx, -368(%rbp)
	movq	-368(%rbp), %rcx
	addq	$1, %rcx
	movq	%rcx, -360(%rbp)
	movq	-360(%rbp), %rcx
	movq	%rcx, -352(%rbp)
	movq	-352(%rbp), %rdi
	movb	$0, -470(%rbp)
	callq	__ZNSt3__111char_traitsIcE6assignERcRKc
	movq	-576(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -432(%rbp)
	movq	$0, -440(%rbp)
	movq	-432(%rbp), %rcx
	movq	-440(%rbp), %rsi
	shlq	$1, %rsi
	movb	%sil, %dl
	movq	%rcx, -424(%rbp)
	movq	-424(%rbp), %rcx
	movq	%rcx, -416(%rbp)
	movq	-416(%rbp), %rcx
	movb	%dl, (%rcx)
LBB6_6:
	movq	-488(%rbp), %rax
	movq	(%rax), %rcx
	movq	-24(%rcx), %rcx
	addq	%rcx, %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -584(%rbp)        ## 8-byte Spill
## BB#7:
	movq	-584(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -528(%rbp)
	cmpq	$0, -528(%rbp)
	jg	LBB6_10
## BB#8:
	movq	-496(%rbp), %rax
	movq	%rax, -272(%rbp)
	movq	-272(%rbp), %rax
	movq	%rax, -264(%rbp)
	movq	-264(%rbp), %rax
	movq	%rax, -256(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, -248(%rbp)
	movq	-248(%rbp), %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	movq	%rax, -184(%rbp)
	movq	$-1, -280(%rbp)
	movq	-280(%rbp), %rax
	subq	$16, %rax
	movq	%rax, -528(%rbp)
	jmp	LBB6_10
LBB6_9:
Ltmp33:
	movl	%edx, %ecx
	movq	%rax, -512(%rbp)
	movl	%ecx, -516(%rbp)
	jmp	LBB6_28
LBB6_10:
	cmpq	$0, -528(%rbp)
	jg	LBB6_12
## BB#11:
	movabsq	$9223372036854775807, %rax ## imm = 0x7FFFFFFFFFFFFFFF
	movq	%rax, -528(%rbp)
LBB6_12:
	movq	$0, -536(%rbp)
	movq	-488(%rbp), %rax
	movq	(%rax), %rcx
	movq	-24(%rcx), %rcx
	addq	%rcx, %rax
Ltmp16:
	leaq	-552(%rbp), %rdi
	movq	%rax, %rsi
	callq	__ZNKSt3__18ios_base6getlocEv
Ltmp17:
	jmp	LBB6_13
LBB6_13:
	leaq	-552(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rdi
Ltmp18:
	movq	__ZNSt3__15ctypeIcE2idE@GOTPCREL(%rip), %rsi
	callq	__ZNKSt3__16locale9use_facetERNS0_2idE
Ltmp19:
	movq	%rax, -592(%rbp)        ## 8-byte Spill
	jmp	LBB6_14
LBB6_14:
	movq	-592(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -600(%rbp)        ## 8-byte Spill
## BB#15:
Ltmp23:
	leaq	-552(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
Ltmp24:
	jmp	LBB6_16
LBB6_16:
	movq	-600(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -544(%rbp)
	movl	$0, -556(%rbp)
LBB6_17:                                ## =>This Inner Loop Header: Depth=1
	movq	-536(%rbp), %rax
	cmpq	-528(%rbp), %rax
	jge	LBB6_45
## BB#18:                               ##   in Loop: Header=BB6_17 Depth=1
	movq	-488(%rbp), %rax
	movq	(%rax), %rcx
	movq	-24(%rcx), %rcx
	addq	%rcx, %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, -608(%rbp)        ## 8-byte Spill
## BB#19:                               ##   in Loop: Header=BB6_17 Depth=1
	movq	-608(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rcx
	movq	24(%rcx), %rdx
	cmpq	32(%rcx), %rdx
	movq	%rcx, -616(%rbp)        ## 8-byte Spill
	jne	LBB6_22
## BB#20:                               ##   in Loop: Header=BB6_17 Depth=1
	movq	-616(%rbp), %rax        ## 8-byte Reload
	movq	(%rax), %rcx
	movq	72(%rcx), %rcx
Ltmp25:
	movq	%rax, %rdi
	callq	*%rcx
Ltmp26:
	movl	%eax, -620(%rbp)        ## 4-byte Spill
	jmp	LBB6_21
LBB6_21:                                ##   in Loop: Header=BB6_17 Depth=1
	movl	-620(%rbp), %eax        ## 4-byte Reload
	movl	%eax, -36(%rbp)
	jmp	LBB6_23
LBB6_22:                                ##   in Loop: Header=BB6_17 Depth=1
	movq	-616(%rbp), %rax        ## 8-byte Reload
	movq	24(%rax), %rcx
	movsbl	(%rcx), %edi
	callq	__ZNSt3__111char_traitsIcE11to_int_typeEc
	movl	%eax, -36(%rbp)
LBB6_23:                                ##   in Loop: Header=BB6_17 Depth=1
	movl	-36(%rbp), %eax
	movl	%eax, -624(%rbp)        ## 4-byte Spill
## BB#24:                               ##   in Loop: Header=BB6_17 Depth=1
	movl	-624(%rbp), %eax        ## 4-byte Reload
	movl	%eax, -560(%rbp)
	movl	-560(%rbp), %edi
	movl	%edi, -628(%rbp)        ## 4-byte Spill
	callq	__ZNSt3__111char_traitsIcE3eofEv
	movl	-628(%rbp), %edi        ## 4-byte Reload
	movl	%eax, %esi
	callq	__ZNSt3__111char_traitsIcE11eq_int_typeEii
	testb	$1, %al
	jne	LBB6_25
	jmp	LBB6_31
LBB6_25:
	movl	-556(%rbp), %eax
	orl	$2, %eax
	movl	%eax, -556(%rbp)
	jmp	LBB6_45
LBB6_26:
Ltmp20:
	movl	%edx, %ecx
	movq	%rax, -512(%rbp)
	movl	%ecx, -516(%rbp)
Ltmp21:
	leaq	-552(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
Ltmp22:
	jmp	LBB6_27
LBB6_27:
	jmp	LBB6_28
LBB6_28:
	movq	-512(%rbp), %rdi
	callq	___cxa_begin_catch
	movq	-488(%rbp), %rdi
	movq	(%rdi), %rcx
	movq	-24(%rcx), %rcx
	addq	%rcx, %rdi
Ltmp34:
	movq	%rax, -640(%rbp)        ## 8-byte Spill
	callq	__ZNSt3__18ios_base33__set_badbit_and_consider_rethrowEv
Ltmp35:
	jmp	LBB6_29
LBB6_29:
	callq	___cxa_end_catch
LBB6_30:
	movq	-488(%rbp), %rax
	addq	$688, %rsp              ## imm = 0x2B0
	popq	%rbp
	retq
LBB6_31:                                ##   in Loop: Header=BB6_17 Depth=1
	movl	-560(%rbp), %edi
	callq	__ZNSt3__111char_traitsIcE12to_char_typeEi
	movb	%al, -561(%rbp)
	movq	-544(%rbp), %rcx
	movb	-561(%rbp), %al
	movq	%rcx, -24(%rbp)
	movl	$16384, -28(%rbp)       ## imm = 0x4000
	movb	%al, -29(%rbp)
	movq	-24(%rbp), %rcx
	movsbl	-29(%rbp), %edi
	movq	%rcx, -648(%rbp)        ## 8-byte Spill
	callq	__Z7isasciii
	cmpl	$0, %eax
	je	LBB6_33
## BB#32:                               ##   in Loop: Header=BB6_17 Depth=1
	movq	-648(%rbp), %rax        ## 8-byte Reload
	movq	16(%rax), %rcx
	movsbl	-29(%rbp), %edx
	movslq	%edx, %rsi
	movl	(%rcx,%rsi,4), %edx
	andl	-28(%rbp), %edx
	cmpl	$0, %edx
	setne	%dil
	movb	%dil, -649(%rbp)        ## 1-byte Spill
	jmp	LBB6_34
LBB6_33:                                ##   in Loop: Header=BB6_17 Depth=1
	xorl	%eax, %eax
	movb	%al, %cl
	movb	%cl, -649(%rbp)         ## 1-byte Spill
	jmp	LBB6_34
LBB6_34:                                ##   in Loop: Header=BB6_17 Depth=1
	movb	-649(%rbp), %al         ## 1-byte Reload
	movb	%al, -650(%rbp)         ## 1-byte Spill
## BB#35:                               ##   in Loop: Header=BB6_17 Depth=1
	movb	-650(%rbp), %al         ## 1-byte Reload
	testb	$1, %al
	jne	LBB6_36
	jmp	LBB6_37
LBB6_36:
	jmp	LBB6_45
LBB6_37:                                ##   in Loop: Header=BB6_17 Depth=1
	movq	-496(%rbp), %rdi
	movsbl	-561(%rbp), %esi
Ltmp27:
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE9push_backEc
Ltmp28:
	jmp	LBB6_38
LBB6_38:                                ##   in Loop: Header=BB6_17 Depth=1
	movq	-536(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -536(%rbp)
	movq	-488(%rbp), %rax
	movq	(%rax), %rcx
	movq	-24(%rcx), %rcx
	addq	%rcx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, -664(%rbp)        ## 8-byte Spill
## BB#39:                               ##   in Loop: Header=BB6_17 Depth=1
	movq	-664(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rcx
	movq	24(%rcx), %rdx
	cmpq	32(%rcx), %rdx
	movq	%rcx, -672(%rbp)        ## 8-byte Spill
	jne	LBB6_42
## BB#40:                               ##   in Loop: Header=BB6_17 Depth=1
	movq	-672(%rbp), %rax        ## 8-byte Reload
	movq	(%rax), %rcx
	movq	80(%rcx), %rcx
Ltmp29:
	movq	%rax, %rdi
	callq	*%rcx
Ltmp30:
	movl	%eax, -676(%rbp)        ## 4-byte Spill
	jmp	LBB6_41
LBB6_41:                                ##   in Loop: Header=BB6_17 Depth=1
	movl	-676(%rbp), %eax        ## 4-byte Reload
	movl	%eax, -52(%rbp)
	jmp	LBB6_43
LBB6_42:                                ##   in Loop: Header=BB6_17 Depth=1
	movq	-672(%rbp), %rax        ## 8-byte Reload
	movq	24(%rax), %rcx
	movq	%rcx, %rdx
	addq	$1, %rdx
	movq	%rdx, 24(%rax)
	movsbl	(%rcx), %edi
	callq	__ZNSt3__111char_traitsIcE11to_int_typeEc
	movl	%eax, -52(%rbp)
LBB6_43:                                ##   in Loop: Header=BB6_17 Depth=1
## BB#44:                               ##   in Loop: Header=BB6_17 Depth=1
	jmp	LBB6_17
LBB6_45:
	movq	-488(%rbp), %rax
	movq	(%rax), %rcx
	movq	-24(%rcx), %rcx
	addq	%rcx, %rax
	movq	%rax, -72(%rbp)
	movq	$0, -80(%rbp)
	movq	-72(%rbp), %rax
	movq	24(%rax), %rcx
	movq	%rcx, -88(%rbp)
	movq	-80(%rbp), %rcx
	movq	%rcx, 24(%rax)
## BB#46:
	cmpq	$0, -536(%rbp)
	jne	LBB6_48
## BB#47:
	movl	-556(%rbp), %eax
	orl	$4, %eax
	movl	%eax, -556(%rbp)
LBB6_48:
	movq	-488(%rbp), %rax
	movq	(%rax), %rcx
	movq	-24(%rcx), %rcx
	addq	%rcx, %rax
	movl	-556(%rbp), %edx
	movq	%rax, -136(%rbp)
	movl	%edx, -140(%rbp)
	movq	-136(%rbp), %rax
	movl	-140(%rbp), %edx
	movq	%rax, -120(%rbp)
	movl	%edx, -124(%rbp)
	movq	-120(%rbp), %rax
	movl	32(%rax), %edx
	movl	-124(%rbp), %esi
	orl	%esi, %edx
Ltmp31:
	movq	%rax, %rdi
	movl	%edx, %esi
	callq	__ZNSt3__18ios_base5clearEj
Ltmp32:
	jmp	LBB6_49
LBB6_49:
	jmp	LBB6_50
LBB6_50:
	jmp	LBB6_54
LBB6_51:
	movq	-488(%rbp), %rax
	movq	(%rax), %rcx
	movq	-24(%rcx), %rcx
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	movl	$4, -172(%rbp)
	movq	-168(%rbp), %rax
	movl	-172(%rbp), %edx
	movq	%rax, -152(%rbp)
	movl	%edx, -156(%rbp)
	movq	-152(%rbp), %rax
	movl	32(%rax), %edx
	movl	-156(%rbp), %esi
	orl	%esi, %edx
Ltmp14:
	movq	%rax, %rdi
	movl	%edx, %esi
	callq	__ZNSt3__18ios_base5clearEj
Ltmp15:
	jmp	LBB6_52
LBB6_52:
	jmp	LBB6_53
LBB6_53:
	jmp	LBB6_54
LBB6_54:
	jmp	LBB6_30
LBB6_55:
Ltmp36:
	movl	%edx, %ecx
	movq	%rax, -512(%rbp)
	movl	%ecx, -516(%rbp)
Ltmp37:
	callq	___cxa_end_catch
Ltmp38:
	jmp	LBB6_56
LBB6_56:
	jmp	LBB6_57
LBB6_57:
	movq	-512(%rbp), %rdi
	callq	__Unwind_Resume
LBB6_58:
Ltmp39:
	movl	%edx, %ecx
	movq	%rax, %rdi
	movl	%ecx, -680(%rbp)        ## 4-byte Spill
	callq	___clang_call_terminate
Lfunc_end2:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table6:
Lexception2:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.asciz	"\213\201"              ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.ascii	"\202\001"              ## Call site table length
Lset22 = Ltmp12-Lfunc_begin2            ## >> Call Site 1 <<
	.long	Lset22
Lset23 = Ltmp17-Ltmp12                  ##   Call between Ltmp12 and Ltmp17
	.long	Lset23
Lset24 = Ltmp33-Lfunc_begin2            ##     jumps to Ltmp33
	.long	Lset24
	.byte	1                       ##   On action: 1
Lset25 = Ltmp18-Lfunc_begin2            ## >> Call Site 2 <<
	.long	Lset25
Lset26 = Ltmp19-Ltmp18                  ##   Call between Ltmp18 and Ltmp19
	.long	Lset26
Lset27 = Ltmp20-Lfunc_begin2            ##     jumps to Ltmp20
	.long	Lset27
	.byte	1                       ##   On action: 1
Lset28 = Ltmp23-Lfunc_begin2            ## >> Call Site 3 <<
	.long	Lset28
Lset29 = Ltmp26-Ltmp23                  ##   Call between Ltmp23 and Ltmp26
	.long	Lset29
Lset30 = Ltmp33-Lfunc_begin2            ##     jumps to Ltmp33
	.long	Lset30
	.byte	1                       ##   On action: 1
Lset31 = Ltmp21-Lfunc_begin2            ## >> Call Site 4 <<
	.long	Lset31
Lset32 = Ltmp22-Ltmp21                  ##   Call between Ltmp21 and Ltmp22
	.long	Lset32
Lset33 = Ltmp39-Lfunc_begin2            ##     jumps to Ltmp39
	.long	Lset33
	.byte	1                       ##   On action: 1
Lset34 = Ltmp22-Lfunc_begin2            ## >> Call Site 5 <<
	.long	Lset34
Lset35 = Ltmp34-Ltmp22                  ##   Call between Ltmp22 and Ltmp34
	.long	Lset35
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset36 = Ltmp34-Lfunc_begin2            ## >> Call Site 6 <<
	.long	Lset36
Lset37 = Ltmp35-Ltmp34                  ##   Call between Ltmp34 and Ltmp35
	.long	Lset37
Lset38 = Ltmp36-Lfunc_begin2            ##     jumps to Ltmp36
	.long	Lset38
	.byte	0                       ##   On action: cleanup
Lset39 = Ltmp35-Lfunc_begin2            ## >> Call Site 7 <<
	.long	Lset39
Lset40 = Ltmp27-Ltmp35                  ##   Call between Ltmp35 and Ltmp27
	.long	Lset40
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset41 = Ltmp27-Lfunc_begin2            ## >> Call Site 8 <<
	.long	Lset41
Lset42 = Ltmp15-Ltmp27                  ##   Call between Ltmp27 and Ltmp15
	.long	Lset42
Lset43 = Ltmp33-Lfunc_begin2            ##     jumps to Ltmp33
	.long	Lset43
	.byte	1                       ##   On action: 1
Lset44 = Ltmp37-Lfunc_begin2            ## >> Call Site 9 <<
	.long	Lset44
Lset45 = Ltmp38-Ltmp37                  ##   Call between Ltmp37 and Ltmp38
	.long	Lset45
Lset46 = Ltmp39-Lfunc_begin2            ##     jumps to Ltmp39
	.long	Lset46
	.byte	1                       ##   On action: 1
Lset47 = Ltmp38-Lfunc_begin2            ## >> Call Site 10 <<
	.long	Lset47
Lset48 = Lfunc_end2-Ltmp38              ##   Call between Ltmp38 and Lfunc_end2
	.long	Lset48
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__ZN10Sales_itemC1Ev    ## -- Begin function _ZN10Sales_itemC1Ev
	.weak_def_can_be_hidden	__ZN10Sales_itemC1Ev
	.p2align	4, 0x90
__ZN10Sales_itemC1Ev:                   ## @_ZN10Sales_itemC1Ev
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi18:
	.cfi_def_cfa_offset 16
Lcfi19:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi20:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	__ZN10Sales_itemC2Ev
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN10Sales_itemaSERKS_ ## -- Begin function _ZN10Sales_itemaSERKS_
	.weak_definition	__ZN10Sales_itemaSERKS_
	.p2align	4, 0x90
__ZN10Sales_itemaSERKS_:                ## @_ZN10Sales_itemaSERKS_
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi21:
	.cfi_def_cfa_offset 16
Lcfi22:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi23:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rsi
	movq	-16(%rbp), %rdi
	movq	%rdi, -24(%rbp)         ## 8-byte Spill
	movq	%rsi, %rdi
	movq	-24(%rbp), %rax         ## 8-byte Reload
	movq	%rsi, -32(%rbp)         ## 8-byte Spill
	movq	%rax, %rsi
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEaSERKS5_
	movq	-16(%rbp), %rsi
	movq	24(%rsi), %rdi
	movq	-32(%rbp), %rcx         ## 8-byte Reload
	movq	%rdi, 24(%rcx)
	movq	32(%rsi), %rsi
	movq	%rsi, 32(%rcx)
	movq	%rax, -40(%rbp)         ## 8-byte Spill
	movq	%rcx, %rax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZlsRNSt3__113basic_ostreamIcNS_11char_traitsIcEEEERK10Sales_item ## -- Begin function _ZlsRNSt3__113basic_ostreamIcNS_11char_traitsIcEEEERK10Sales_item
	.p2align	4, 0x90
__ZlsRNSt3__113basic_ostreamIcNS_11char_traitsIcEEEERK10Sales_item: ## @_ZlsRNSt3__113basic_ostreamIcNS_11char_traitsIcEEEERK10Sales_item
Lfunc_begin3:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception3
## BB#0:
	pushq	%rbp
Lcfi24:
	.cfi_def_cfa_offset 16
Lcfi25:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi26:
	.cfi_def_cfa_register %rbp
	subq	$144, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	leaq	-40(%rbp), %rax
	movq	%rdi, -64(%rbp)         ## 8-byte Spill
	movq	%rax, %rdi
	movq	%rax, -72(%rbp)         ## 8-byte Spill
	callq	__ZNK10Sales_item4isbnEv
Ltmp40:
	movq	-64(%rbp), %rdi         ## 8-byte Reload
	movq	-72(%rbp), %rsi         ## 8-byte Reload
	callq	__ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE
Ltmp41:
	movq	%rax, -80(%rbp)         ## 8-byte Spill
	jmp	LBB9_1
LBB9_1:
Ltmp42:
	leaq	L_.str(%rip), %rsi
	movq	-80(%rbp), %rdi         ## 8-byte Reload
	callq	__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
Ltmp43:
	movq	%rax, -88(%rbp)         ## 8-byte Spill
	jmp	LBB9_2
LBB9_2:
	movq	-16(%rbp), %rax
	movl	24(%rax), %esi
Ltmp44:
	movq	-88(%rbp), %rdi         ## 8-byte Reload
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEj
Ltmp45:
	movq	%rax, -96(%rbp)         ## 8-byte Spill
	jmp	LBB9_3
LBB9_3:
Ltmp46:
	leaq	L_.str(%rip), %rsi
	movq	-96(%rbp), %rdi         ## 8-byte Reload
	callq	__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
Ltmp47:
	movq	%rax, -104(%rbp)        ## 8-byte Spill
	jmp	LBB9_4
LBB9_4:
	movq	-16(%rbp), %rax
	movsd	32(%rax), %xmm0         ## xmm0 = mem[0],zero
Ltmp48:
	movq	-104(%rbp), %rdi        ## 8-byte Reload
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEd
Ltmp49:
	movq	%rax, -112(%rbp)        ## 8-byte Spill
	jmp	LBB9_5
LBB9_5:
Ltmp50:
	leaq	L_.str(%rip), %rsi
	movq	-112(%rbp), %rdi        ## 8-byte Reload
	callq	__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
Ltmp51:
	movq	%rax, -120(%rbp)        ## 8-byte Spill
	jmp	LBB9_6
LBB9_6:
	movq	-16(%rbp), %rdi
Ltmp52:
	callq	__ZNK10Sales_item9avg_priceEv
Ltmp53:
	movsd	%xmm0, -128(%rbp)       ## 8-byte Spill
	jmp	LBB9_7
LBB9_7:
Ltmp54:
	movq	-120(%rbp), %rdi        ## 8-byte Reload
	movsd	-128(%rbp), %xmm0       ## 8-byte Reload
                                        ## xmm0 = mem[0],zero
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEd
Ltmp55:
	movq	%rax, -136(%rbp)        ## 8-byte Spill
	jmp	LBB9_8
LBB9_8:
	leaq	-40(%rbp), %rdi
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev
	movq	-8(%rbp), %rax
	addq	$144, %rsp
	popq	%rbp
	retq
LBB9_9:
Ltmp56:
	movl	%edx, %ecx
	movq	%rax, -48(%rbp)
	movl	%ecx, -52(%rbp)
Ltmp57:
	leaq	-40(%rbp), %rdi
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev
Ltmp58:
	jmp	LBB9_10
LBB9_10:
	jmp	LBB9_11
LBB9_11:
	movq	-48(%rbp), %rdi
	callq	__Unwind_Resume
LBB9_12:
Ltmp59:
	movl	%edx, %ecx
	movq	%rax, %rdi
	movl	%ecx, -140(%rbp)        ## 4-byte Spill
	callq	___clang_call_terminate
Lfunc_end3:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table9:
Lexception3:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.byte	73                      ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.byte	65                      ## Call site table length
Lset49 = Lfunc_begin3-Lfunc_begin3      ## >> Call Site 1 <<
	.long	Lset49
Lset50 = Ltmp40-Lfunc_begin3            ##   Call between Lfunc_begin3 and Ltmp40
	.long	Lset50
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset51 = Ltmp40-Lfunc_begin3            ## >> Call Site 2 <<
	.long	Lset51
Lset52 = Ltmp55-Ltmp40                  ##   Call between Ltmp40 and Ltmp55
	.long	Lset52
Lset53 = Ltmp56-Lfunc_begin3            ##     jumps to Ltmp56
	.long	Lset53
	.byte	0                       ##   On action: cleanup
Lset54 = Ltmp55-Lfunc_begin3            ## >> Call Site 3 <<
	.long	Lset54
Lset55 = Ltmp57-Ltmp55                  ##   Call between Ltmp55 and Ltmp57
	.long	Lset55
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset56 = Ltmp57-Lfunc_begin3            ## >> Call Site 4 <<
	.long	Lset56
Lset57 = Ltmp58-Ltmp57                  ##   Call between Ltmp57 and Ltmp58
	.long	Lset57
Lset58 = Ltmp59-Lfunc_begin3            ##     jumps to Ltmp59
	.long	Lset58
	.byte	1                       ##   On action: 1
Lset59 = Ltmp58-Lfunc_begin3            ## >> Call Site 5 <<
	.long	Lset59
Lset60 = Lfunc_end3-Ltmp58              ##   Call between Ltmp58 and Lfunc_end3
	.long	Lset60
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc ## -- Begin function _ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
	.weak_definition	__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
	.p2align	4, 0x90
__ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc: ## @_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi27:
	.cfi_def_cfa_offset 16
Lcfi28:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi29:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movq	-16(%rbp), %rax
	movq	%rdi, -24(%rbp)         ## 8-byte Spill
	movq	%rax, %rdi
	movq	%rsi, -32(%rbp)         ## 8-byte Spill
	callq	__ZNSt3__111char_traitsIcE6lengthEPKc
	movq	-24(%rbp), %rdi         ## 8-byte Reload
	movq	-32(%rbp), %rsi         ## 8-byte Reload
	movq	%rax, %rdx
	callq	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE ## -- Begin function _ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE
	.weak_definition	__ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE
	.p2align	4, 0x90
__ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE: ## @_ZNSt3__1lsIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS_13basic_ostreamIT_T0_EES9_RKNS_12basic_stringIS6_S7_T1_EE
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi30:
	.cfi_def_cfa_offset 16
Lcfi31:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi32:
	.cfi_def_cfa_register %rbp
	subq	$256, %rsp              ## imm = 0x100
	movq	%rdi, -200(%rbp)
	movq	%rsi, -208(%rbp)
	movq	-200(%rbp), %rdi
	movq	-208(%rbp), %rsi
	movq	%rsi, -192(%rbp)
	movq	-192(%rbp), %rsi
	movq	%rsi, -184(%rbp)
	movq	-184(%rbp), %rsi
	movq	%rsi, -176(%rbp)
	movq	-176(%rbp), %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movzbl	(%rax), %ecx
	movl	%ecx, %eax
	andq	$1, %rax
	cmpq	$0, %rax
	movq	%rdi, -216(%rbp)        ## 8-byte Spill
	movq	%rsi, -224(%rbp)        ## 8-byte Spill
	je	LBB11_2
## BB#1:
	movq	-224(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rcx
	movq	%rcx, -104(%rbp)
	movq	-104(%rbp), %rcx
	movq	%rcx, -96(%rbp)
	movq	-96(%rbp), %rcx
	movq	16(%rcx), %rcx
	movq	%rcx, -232(%rbp)        ## 8-byte Spill
	jmp	LBB11_3
LBB11_2:
	movq	-224(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -152(%rbp)
	movq	-152(%rbp), %rcx
	movq	%rcx, -144(%rbp)
	movq	-144(%rbp), %rcx
	movq	%rcx, -136(%rbp)
	movq	-136(%rbp), %rcx
	addq	$1, %rcx
	movq	%rcx, -128(%rbp)
	movq	-128(%rbp), %rcx
	movq	%rcx, -120(%rbp)
	movq	-120(%rbp), %rcx
	movq	%rcx, -232(%rbp)        ## 8-byte Spill
LBB11_3:
	movq	-232(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rsi
	movq	-208(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rcx
	movq	%rcx, -64(%rbp)
	movq	-64(%rbp), %rcx
	movq	%rcx, -56(%rbp)
	movq	-56(%rbp), %rcx
	movzbl	(%rcx), %edx
	movl	%edx, %ecx
	andq	$1, %rcx
	cmpq	$0, %rcx
	movq	%rsi, -240(%rbp)        ## 8-byte Spill
	movq	%rax, -248(%rbp)        ## 8-byte Spill
	je	LBB11_5
## BB#4:
	movq	-248(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rcx
	movq	%rcx, -16(%rbp)
	movq	-16(%rbp), %rcx
	movq	%rcx, -8(%rbp)
	movq	-8(%rbp), %rcx
	movq	8(%rcx), %rcx
	movq	%rcx, -256(%rbp)        ## 8-byte Spill
	jmp	LBB11_6
LBB11_5:
	movq	-248(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rcx
	movq	%rcx, -40(%rbp)
	movq	-40(%rbp), %rcx
	movq	%rcx, -32(%rbp)
	movq	-32(%rbp), %rcx
	movzbl	(%rcx), %edx
	sarl	$1, %edx
	movslq	%edx, %rcx
	movq	%rcx, -256(%rbp)        ## 8-byte Spill
LBB11_6:
	movq	-256(%rbp), %rax        ## 8-byte Reload
	movq	-216(%rbp), %rdi        ## 8-byte Reload
	movq	-240(%rbp), %rsi        ## 8-byte Reload
	movq	%rax, %rdx
	callq	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	addq	$256, %rsp              ## imm = 0x100
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNK10Sales_item4isbnEv ## -- Begin function _ZNK10Sales_item4isbnEv
	.weak_definition	__ZNK10Sales_item4isbnEv
	.p2align	4, 0x90
__ZNK10Sales_item4isbnEv:               ## @_ZNK10Sales_item4isbnEv
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi33:
	.cfi_def_cfa_offset 16
Lcfi34:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi35:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, %rax
	movq	%rsi, -8(%rbp)
	movq	-8(%rbp), %rsi
	movq	%rax, -16(%rbp)         ## 8-byte Spill
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1ERKS5_
	movq	-16(%rbp), %rax         ## 8-byte Reload
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNK10Sales_item9avg_priceEv ## -- Begin function _ZNK10Sales_item9avg_priceEv
	.p2align	4, 0x90
__ZNK10Sales_item9avg_priceEv:          ## @_ZNK10Sales_item9avg_priceEv
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi36:
	.cfi_def_cfa_offset 16
Lcfi37:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi38:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rdi
	cmpl	$0, 24(%rdi)
	movq	%rdi, -24(%rbp)         ## 8-byte Spill
	je	LBB13_2
## BB#1:
	movq	-24(%rbp), %rax         ## 8-byte Reload
	movsd	32(%rax), %xmm0         ## xmm0 = mem[0],zero
	movl	24(%rax), %ecx
	movl	%ecx, %edx
	cvtsi2sdq	%rdx, %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	jmp	LBB13_3
LBB13_2:
	xorps	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
LBB13_3:
	movsd	-8(%rbp), %xmm0         ## xmm0 = mem[0],zero
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi39:
	.cfi_def_cfa_offset 16
Lcfi40:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi41:
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	leaq	-48(%rbp), %rax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	%rcx, -8(%rbp)
	movl	$0, -52(%rbp)
	movq	%rax, %rcx
	addq	$4, %rcx
	movq	%rcx, -64(%rbp)
	movq	%rax, %rcx
	addq	$20, %rcx
	movq	%rcx, -72(%rbp)
	movq	%rax, -80(%rbp)
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rcx
	cmpq	%rcx, %rax
	jne	LBB14_2
## BB#1:
	xorl	%eax, %eax
	addq	$80, %rsp
	popq	%rbp
	retq
LBB14_2:
	callq	___stack_chk_fail
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN10Sales_itemC2ERKS_ ## -- Begin function _ZN10Sales_itemC2ERKS_
	.weak_def_can_be_hidden	__ZN10Sales_itemC2ERKS_
	.p2align	4, 0x90
__ZN10Sales_itemC2ERKS_:                ## @_ZN10Sales_itemC2ERKS_
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi42:
	.cfi_def_cfa_offset 16
Lcfi43:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi44:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rsi
	movq	-16(%rbp), %rdi
	movq	%rdi, -24(%rbp)         ## 8-byte Spill
	movq	%rsi, %rdi
	movq	-24(%rbp), %rax         ## 8-byte Reload
	movq	%rsi, -32(%rbp)         ## 8-byte Spill
	movq	%rax, %rsi
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1ERKS5_
	movq	-16(%rbp), %rax
	movq	24(%rax), %rsi
	movq	-32(%rbp), %rdi         ## 8-byte Reload
	movq	%rsi, 24(%rdi)
	movq	32(%rax), %rax
	movq	%rax, 32(%rdi)
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN10Sales_itemD2Ev    ## -- Begin function _ZN10Sales_itemD2Ev
	.weak_def_can_be_hidden	__ZN10Sales_itemD2Ev
	.p2align	4, 0x90
__ZN10Sales_itemD2Ev:                   ## @_ZN10Sales_itemD2Ev
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi45:
	.cfi_def_cfa_offset 16
Lcfi46:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi47:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN10Sales_itemC2Ev    ## -- Begin function _ZN10Sales_itemC2Ev
	.weak_def_can_be_hidden	__ZN10Sales_itemC2Ev
	.p2align	4, 0x90
__ZN10Sales_itemC2Ev:                   ## @_ZN10Sales_itemC2Ev
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi48:
	.cfi_def_cfa_offset 16
Lcfi49:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi50:
	.cfi_def_cfa_register %rbp
	subq	$128, %rsp
	xorl	%esi, %esi
	movl	$24, %eax
	movl	%eax, %edx
	movq	%rdi, -104(%rbp)
	movq	-104(%rbp), %rdi
	movq	%rdi, -96(%rbp)
	movq	-96(%rbp), %rcx
	movq	%rcx, -88(%rbp)
	movq	-88(%rbp), %rcx
	movq	%rcx, -80(%rbp)
	movq	-80(%rbp), %r8
	movq	%r8, -72(%rbp)
	movq	-72(%rbp), %r8
	movq	%r8, %r9
	movq	%r9, -64(%rbp)
	movq	-64(%rbp), %r9
	movq	%rdi, -112(%rbp)        ## 8-byte Spill
	movq	%r9, %rdi
	movq	%r8, -120(%rbp)         ## 8-byte Spill
	movq	%rcx, -128(%rbp)        ## 8-byte Spill
	callq	_memset
	movq	-120(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -56(%rbp)
	movq	-56(%rbp), %rcx
	movq	%rcx, -48(%rbp)
	movq	-128(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	%rdx, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	%rdx, -32(%rbp)
	movl	$0, -36(%rbp)
LBB17_1:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$3, -36(%rbp)
	jae	LBB17_3
## BB#2:                                ##   in Loop: Header=BB17_1 Depth=1
	movq	-32(%rbp), %rax
	movl	-36(%rbp), %ecx
	movl	%ecx, %edx
	movq	$0, (%rax,%rdx,8)
	movl	-36(%rbp), %ecx
	addl	$1, %ecx
	movl	%ecx, -36(%rbp)
	jmp	LBB17_1
LBB17_3:
	xorps	%xmm0, %xmm0
	movq	-112(%rbp), %rax        ## 8-byte Reload
	movl	$0, 24(%rax)
	movsd	%xmm0, 32(%rax)
	addq	$128, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__111char_traitsIcE11eq_int_typeEii ## -- Begin function _ZNSt3__111char_traitsIcE11eq_int_typeEii
	.weak_definition	__ZNSt3__111char_traitsIcE11eq_int_typeEii
	.p2align	4, 0x90
__ZNSt3__111char_traitsIcE11eq_int_typeEii: ## @_ZNSt3__111char_traitsIcE11eq_int_typeEii
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi51:
	.cfi_def_cfa_offset 16
Lcfi52:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi53:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %esi
	cmpl	-8(%rbp), %esi
	sete	%al
	andb	$1, %al
	movzbl	%al, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__111char_traitsIcE3eofEv ## -- Begin function _ZNSt3__111char_traitsIcE3eofEv
	.weak_definition	__ZNSt3__111char_traitsIcE3eofEv
	.p2align	4, 0x90
__ZNSt3__111char_traitsIcE3eofEv:       ## @_ZNSt3__111char_traitsIcE3eofEv
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi54:
	.cfi_def_cfa_offset 16
Lcfi55:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi56:
	.cfi_def_cfa_register %rbp
	movl	$4294967295, %eax       ## imm = 0xFFFFFFFF
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__111char_traitsIcE12to_char_typeEi ## -- Begin function _ZNSt3__111char_traitsIcE12to_char_typeEi
	.weak_definition	__ZNSt3__111char_traitsIcE12to_char_typeEi
	.p2align	4, 0x90
__ZNSt3__111char_traitsIcE12to_char_typeEi: ## @_ZNSt3__111char_traitsIcE12to_char_typeEi
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi57:
	.cfi_def_cfa_offset 16
Lcfi58:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi59:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %edi
	movb	%dil, %al
	movsbl	%al, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__111char_traitsIcE6assignERcRKc ## -- Begin function _ZNSt3__111char_traitsIcE6assignERcRKc
	.weak_definition	__ZNSt3__111char_traitsIcE6assignERcRKc
	.p2align	4, 0x90
__ZNSt3__111char_traitsIcE6assignERcRKc: ## @_ZNSt3__111char_traitsIcE6assignERcRKc
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi60:
	.cfi_def_cfa_offset 16
Lcfi61:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi62:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rsi
	movb	(%rsi), %al
	movq	-8(%rbp), %rsi
	movb	%al, (%rsi)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__111char_traitsIcE11to_int_typeEc ## -- Begin function _ZNSt3__111char_traitsIcE11to_int_typeEc
	.weak_definition	__ZNSt3__111char_traitsIcE11to_int_typeEc
	.p2align	4, 0x90
__ZNSt3__111char_traitsIcE11to_int_typeEc: ## @_ZNSt3__111char_traitsIcE11to_int_typeEc
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi63:
	.cfi_def_cfa_offset 16
Lcfi64:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi65:
	.cfi_def_cfa_register %rbp
	movb	%dil, %al
	movb	%al, -1(%rbp)
	movzbl	-1(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z7isasciii            ## -- Begin function _Z7isasciii
	.weak_definition	__Z7isasciii
	.p2align	4, 0x90
__Z7isasciii:                           ## @_Z7isasciii
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi66:
	.cfi_def_cfa_offset 16
Lcfi67:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi68:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %edi
	andl	$-128, %edi
	cmpl	$0, %edi
	sete	%al
	andb	$1, %al
	movzbl	%al, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__112__cxx03_bool12__true_valueEv ## -- Begin function _ZNSt3__112__cxx03_bool12__true_valueEv
	.weak_definition	__ZNSt3__112__cxx03_bool12__true_valueEv
	.p2align	4, 0x90
__ZNSt3__112__cxx03_bool12__true_valueEv: ## @_ZNSt3__112__cxx03_bool12__true_valueEv
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi69:
	.cfi_def_cfa_offset 16
Lcfi70:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi71:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m ## -- Begin function _ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	.weak_definition	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	.p2align	4, 0x90
__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m: ## @_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
Lfunc_begin4:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception4
## BB#0:
	pushq	%rbp
Lcfi72:
	.cfi_def_cfa_offset 16
Lcfi73:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi74:
	.cfi_def_cfa_register %rbp
	subq	$416, %rsp              ## imm = 0x1A0
	movq	%rdi, -200(%rbp)
	movq	%rsi, -208(%rbp)
	movq	%rdx, -216(%rbp)
	movq	-200(%rbp), %rsi
Ltmp60:
	leaq	-232(%rbp), %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_
Ltmp61:
	jmp	LBB25_1
LBB25_1:
	leaq	-232(%rbp), %rax
	movq	%rax, -192(%rbp)
	movq	-192(%rbp), %rax
	movb	(%rax), %cl
	movb	%cl, -265(%rbp)         ## 1-byte Spill
## BB#2:
	movb	-265(%rbp), %al         ## 1-byte Reload
	testb	$1, %al
	jne	LBB25_3
	jmp	LBB25_26
LBB25_3:
	leaq	-256(%rbp), %rax
	movq	-200(%rbp), %rcx
	movq	%rax, -176(%rbp)
	movq	%rcx, -184(%rbp)
	movq	-176(%rbp), %rax
	movq	-184(%rbp), %rcx
	movq	%rax, -144(%rbp)
	movq	%rcx, -152(%rbp)
	movq	-144(%rbp), %rax
	movq	-152(%rbp), %rcx
	movq	(%rcx), %rdx
	movq	-24(%rdx), %rdx
	addq	%rdx, %rcx
	movq	%rcx, -136(%rbp)
	movq	-136(%rbp), %rcx
	movq	%rcx, -128(%rbp)
	movq	-128(%rbp), %rcx
	movq	40(%rcx), %rcx
	movq	%rcx, (%rax)
	movq	-208(%rbp), %rsi
	movq	-200(%rbp), %rax
	movq	(%rax), %rcx
	movq	-24(%rcx), %rcx
	addq	%rcx, %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movl	8(%rax), %edi
	movq	%rsi, -280(%rbp)        ## 8-byte Spill
	movl	%edi, -284(%rbp)        ## 4-byte Spill
## BB#4:
	movl	-284(%rbp), %eax        ## 4-byte Reload
	andl	$176, %eax
	cmpl	$32, %eax
	jne	LBB25_6
## BB#5:
	movq	-208(%rbp), %rax
	addq	-216(%rbp), %rax
	movq	%rax, -296(%rbp)        ## 8-byte Spill
	jmp	LBB25_7
LBB25_6:
	movq	-208(%rbp), %rax
	movq	%rax, -296(%rbp)        ## 8-byte Spill
LBB25_7:
	movq	-296(%rbp), %rax        ## 8-byte Reload
	movq	-208(%rbp), %rcx
	addq	-216(%rbp), %rcx
	movq	-200(%rbp), %rdx
	movq	(%rdx), %rsi
	movq	-24(%rsi), %rsi
	addq	%rsi, %rdx
	movq	-200(%rbp), %rsi
	movq	(%rsi), %rdi
	movq	-24(%rdi), %rdi
	addq	%rdi, %rsi
	movq	%rsi, -72(%rbp)
	movq	-72(%rbp), %rsi
	movq	%rax, -304(%rbp)        ## 8-byte Spill
	movq	%rcx, -312(%rbp)        ## 8-byte Spill
	movq	%rdx, -320(%rbp)        ## 8-byte Spill
	movq	%rsi, -328(%rbp)        ## 8-byte Spill
	callq	__ZNSt3__111char_traitsIcE3eofEv
	movq	-328(%rbp), %rcx        ## 8-byte Reload
	movl	144(%rcx), %esi
	movl	%eax, %edi
	callq	__ZNSt3__111char_traitsIcE11eq_int_typeEii
	testb	$1, %al
	jne	LBB25_8
	jmp	LBB25_16
LBB25_8:
	movq	-328(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -32(%rbp)
	movb	$32, -33(%rbp)
	movq	-32(%rbp), %rsi
Ltmp62:
	leaq	-48(%rbp), %rdi
	callq	__ZNKSt3__18ios_base6getlocEv
Ltmp63:
	jmp	LBB25_9
LBB25_9:
	leaq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rdi
Ltmp64:
	movq	__ZNSt3__15ctypeIcE2idE@GOTPCREL(%rip), %rsi
	callq	__ZNKSt3__16locale9use_facetERNS0_2idE
Ltmp65:
	movq	%rax, -336(%rbp)        ## 8-byte Spill
	jmp	LBB25_10
LBB25_10:
	movb	-33(%rbp), %al
	movq	-336(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -8(%rbp)
	movb	%al, -9(%rbp)
	movq	-8(%rbp), %rdx
	movq	(%rdx), %rsi
	movq	56(%rsi), %rsi
	movsbl	-9(%rbp), %edi
Ltmp66:
	movl	%edi, -340(%rbp)        ## 4-byte Spill
	movq	%rdx, %rdi
	movl	-340(%rbp), %r8d        ## 4-byte Reload
	movq	%rsi, -352(%rbp)        ## 8-byte Spill
	movl	%r8d, %esi
	movq	-352(%rbp), %rdx        ## 8-byte Reload
	callq	*%rdx
Ltmp67:
	movb	%al, -353(%rbp)         ## 1-byte Spill
	jmp	LBB25_14
LBB25_11:
Ltmp68:
	movl	%edx, %ecx
	movq	%rax, -56(%rbp)
	movl	%ecx, -60(%rbp)
Ltmp69:
	leaq	-48(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
Ltmp70:
	jmp	LBB25_12
LBB25_12:
	movq	-56(%rbp), %rax
	movl	-60(%rbp), %ecx
	movq	%rax, -368(%rbp)        ## 8-byte Spill
	movl	%ecx, -372(%rbp)        ## 4-byte Spill
	jmp	LBB25_24
LBB25_13:
Ltmp71:
	movl	%edx, %ecx
	movq	%rax, %rdi
	movl	%ecx, -376(%rbp)        ## 4-byte Spill
	callq	___clang_call_terminate
LBB25_14:
Ltmp72:
	leaq	-48(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
Ltmp73:
	jmp	LBB25_15
LBB25_15:
	movb	-353(%rbp), %al         ## 1-byte Reload
	movsbl	%al, %ecx
	movq	-328(%rbp), %rdx        ## 8-byte Reload
	movl	%ecx, 144(%rdx)
LBB25_16:
	movq	-328(%rbp), %rax        ## 8-byte Reload
	movl	144(%rax), %ecx
	movb	%cl, %dl
	movb	%dl, -377(%rbp)         ## 1-byte Spill
## BB#17:
	movq	-256(%rbp), %rdi
Ltmp74:
	movb	-377(%rbp), %al         ## 1-byte Reload
	movsbl	%al, %r9d
	movq	-280(%rbp), %rsi        ## 8-byte Reload
	movq	-304(%rbp), %rdx        ## 8-byte Reload
	movq	-312(%rbp), %rcx        ## 8-byte Reload
	movq	-320(%rbp), %r8         ## 8-byte Reload
	callq	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
Ltmp75:
	movq	%rax, -392(%rbp)        ## 8-byte Spill
	jmp	LBB25_18
LBB25_18:
	leaq	-264(%rbp), %rax
	movq	-392(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -264(%rbp)
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	cmpq	$0, (%rax)
	jne	LBB25_25
## BB#19:
	movq	-200(%rbp), %rax
	movq	(%rax), %rcx
	movq	-24(%rcx), %rcx
	addq	%rcx, %rax
	movq	%rax, -112(%rbp)
	movl	$5, -116(%rbp)
	movq	-112(%rbp), %rax
	movl	-116(%rbp), %edx
	movq	%rax, -96(%rbp)
	movl	%edx, -100(%rbp)
	movq	-96(%rbp), %rax
	movl	32(%rax), %edx
	movl	-100(%rbp), %esi
	orl	%esi, %edx
Ltmp76:
	movq	%rax, %rdi
	movl	%edx, %esi
	callq	__ZNSt3__18ios_base5clearEj
Ltmp77:
	jmp	LBB25_20
LBB25_20:
	jmp	LBB25_21
LBB25_21:
	jmp	LBB25_25
LBB25_22:
Ltmp83:
	movl	%edx, %ecx
	movq	%rax, -240(%rbp)
	movl	%ecx, -244(%rbp)
	jmp	LBB25_29
LBB25_23:
Ltmp78:
	movl	%edx, %ecx
	movq	%rax, -368(%rbp)        ## 8-byte Spill
	movl	%ecx, -372(%rbp)        ## 4-byte Spill
	jmp	LBB25_24
LBB25_24:
	movl	-372(%rbp), %eax        ## 4-byte Reload
	movq	-368(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -240(%rbp)
	movl	%eax, -244(%rbp)
Ltmp79:
	leaq	-232(%rbp), %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev
Ltmp80:
	jmp	LBB25_28
LBB25_25:
	jmp	LBB25_26
LBB25_26:
Ltmp81:
	leaq	-232(%rbp), %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev
Ltmp82:
	jmp	LBB25_27
LBB25_27:
	jmp	LBB25_31
LBB25_28:
	jmp	LBB25_29
LBB25_29:
	movq	-240(%rbp), %rdi
	callq	___cxa_begin_catch
	movq	-200(%rbp), %rdi
	movq	(%rdi), %rcx
	movq	-24(%rcx), %rcx
	addq	%rcx, %rdi
Ltmp84:
	movq	%rax, -400(%rbp)        ## 8-byte Spill
	callq	__ZNSt3__18ios_base33__set_badbit_and_consider_rethrowEv
Ltmp85:
	jmp	LBB25_30
LBB25_30:
	callq	___cxa_end_catch
LBB25_31:
	movq	-200(%rbp), %rax
	addq	$416, %rsp              ## imm = 0x1A0
	popq	%rbp
	retq
LBB25_32:
Ltmp86:
	movl	%edx, %ecx
	movq	%rax, -240(%rbp)
	movl	%ecx, -244(%rbp)
Ltmp87:
	callq	___cxa_end_catch
Ltmp88:
	jmp	LBB25_33
LBB25_33:
	jmp	LBB25_34
LBB25_34:
	movq	-240(%rbp), %rdi
	callq	__Unwind_Resume
LBB25_35:
Ltmp89:
	movl	%edx, %ecx
	movq	%rax, %rdi
	movl	%ecx, -404(%rbp)        ## 4-byte Spill
	callq	___clang_call_terminate
Lfunc_end4:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table25:
Lexception4:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.asciz	"\253\201"              ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.ascii	"\234\001"              ## Call site table length
Lset61 = Ltmp60-Lfunc_begin4            ## >> Call Site 1 <<
	.long	Lset61
Lset62 = Ltmp61-Ltmp60                  ##   Call between Ltmp60 and Ltmp61
	.long	Lset62
Lset63 = Ltmp83-Lfunc_begin4            ##     jumps to Ltmp83
	.long	Lset63
	.byte	5                       ##   On action: 3
Lset64 = Ltmp62-Lfunc_begin4            ## >> Call Site 2 <<
	.long	Lset64
Lset65 = Ltmp63-Ltmp62                  ##   Call between Ltmp62 and Ltmp63
	.long	Lset65
Lset66 = Ltmp78-Lfunc_begin4            ##     jumps to Ltmp78
	.long	Lset66
	.byte	5                       ##   On action: 3
Lset67 = Ltmp64-Lfunc_begin4            ## >> Call Site 3 <<
	.long	Lset67
Lset68 = Ltmp67-Ltmp64                  ##   Call between Ltmp64 and Ltmp67
	.long	Lset68
Lset69 = Ltmp68-Lfunc_begin4            ##     jumps to Ltmp68
	.long	Lset69
	.byte	3                       ##   On action: 2
Lset70 = Ltmp69-Lfunc_begin4            ## >> Call Site 4 <<
	.long	Lset70
Lset71 = Ltmp70-Ltmp69                  ##   Call between Ltmp69 and Ltmp70
	.long	Lset71
Lset72 = Ltmp71-Lfunc_begin4            ##     jumps to Ltmp71
	.long	Lset72
	.byte	7                       ##   On action: 4
Lset73 = Ltmp72-Lfunc_begin4            ## >> Call Site 5 <<
	.long	Lset73
Lset74 = Ltmp77-Ltmp72                  ##   Call between Ltmp72 and Ltmp77
	.long	Lset74
Lset75 = Ltmp78-Lfunc_begin4            ##     jumps to Ltmp78
	.long	Lset75
	.byte	5                       ##   On action: 3
Lset76 = Ltmp79-Lfunc_begin4            ## >> Call Site 6 <<
	.long	Lset76
Lset77 = Ltmp80-Ltmp79                  ##   Call between Ltmp79 and Ltmp80
	.long	Lset77
Lset78 = Ltmp89-Lfunc_begin4            ##     jumps to Ltmp89
	.long	Lset78
	.byte	5                       ##   On action: 3
Lset79 = Ltmp81-Lfunc_begin4            ## >> Call Site 7 <<
	.long	Lset79
Lset80 = Ltmp82-Ltmp81                  ##   Call between Ltmp81 and Ltmp82
	.long	Lset80
Lset81 = Ltmp83-Lfunc_begin4            ##     jumps to Ltmp83
	.long	Lset81
	.byte	5                       ##   On action: 3
Lset82 = Ltmp82-Lfunc_begin4            ## >> Call Site 8 <<
	.long	Lset82
Lset83 = Ltmp84-Ltmp82                  ##   Call between Ltmp82 and Ltmp84
	.long	Lset83
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset84 = Ltmp84-Lfunc_begin4            ## >> Call Site 9 <<
	.long	Lset84
Lset85 = Ltmp85-Ltmp84                  ##   Call between Ltmp84 and Ltmp85
	.long	Lset85
Lset86 = Ltmp86-Lfunc_begin4            ##     jumps to Ltmp86
	.long	Lset86
	.byte	0                       ##   On action: cleanup
Lset87 = Ltmp85-Lfunc_begin4            ## >> Call Site 10 <<
	.long	Lset87
Lset88 = Ltmp87-Ltmp85                  ##   Call between Ltmp85 and Ltmp87
	.long	Lset88
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset89 = Ltmp87-Lfunc_begin4            ## >> Call Site 11 <<
	.long	Lset89
Lset90 = Ltmp88-Ltmp87                  ##   Call between Ltmp87 and Ltmp88
	.long	Lset90
Lset91 = Ltmp89-Lfunc_begin4            ##     jumps to Ltmp89
	.long	Lset91
	.byte	5                       ##   On action: 3
Lset92 = Ltmp88-Lfunc_begin4            ## >> Call Site 12 <<
	.long	Lset92
Lset93 = Lfunc_end4-Ltmp88              ##   Call between Ltmp88 and Lfunc_end4
	.long	Lset93
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	0                       ## >> Action Record 1 <<
                                        ##   Cleanup
	.byte	0                       ##   No further actions
	.byte	1                       ## >> Action Record 2 <<
                                        ##   Catch TypeInfo 1
	.byte	125                     ##   Continue to action 1
	.byte	1                       ## >> Action Record 3 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
	.byte	1                       ## >> Action Record 4 <<
                                        ##   Catch TypeInfo 1
	.byte	125                     ##   Continue to action 3
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.private_extern	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_ ## -- Begin function _ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.globl	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.weak_definition	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.p2align	4, 0x90
__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_: ## @_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
Lfunc_begin5:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception5
## BB#0:
	pushq	%rbp
Lcfi75:
	.cfi_def_cfa_offset 16
Lcfi76:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi77:
	.cfi_def_cfa_register %rbp
	subq	$736, %rsp              ## imm = 0x2E0
	movb	%r9b, %al
	leaq	-560(%rbp), %r10
	leaq	-496(%rbp), %r11
	movq	%rdi, -512(%rbp)
	movq	%rsi, -520(%rbp)
	movq	%rdx, -528(%rbp)
	movq	%rcx, -536(%rbp)
	movq	%r8, -544(%rbp)
	movb	%al, -545(%rbp)
	movq	-512(%rbp), %rcx
	movq	%r11, -480(%rbp)
	movq	$-1, -488(%rbp)
	movq	-480(%rbp), %rdx
	movq	-488(%rbp), %rsi
	movq	%rdx, -464(%rbp)
	movq	%rsi, -472(%rbp)
	movq	-464(%rbp), %rdx
	movq	$0, (%rdx)
	movq	-496(%rbp), %rdx
	movq	%rdx, -560(%rbp)
	movq	%r10, -456(%rbp)
	cmpq	$0, %rcx
	jne	LBB26_2
## BB#1:
	movq	-512(%rbp), %rax
	movq	%rax, -504(%rbp)
	jmp	LBB26_29
LBB26_2:
	movq	-536(%rbp), %rax
	movq	-520(%rbp), %rcx
	subq	%rcx, %rax
	movq	%rax, -568(%rbp)
	movq	-544(%rbp), %rax
	movq	%rax, -352(%rbp)
	movq	-352(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -576(%rbp)
	movq	-576(%rbp), %rax
	cmpq	-568(%rbp), %rax
	jle	LBB26_4
## BB#3:
	movq	-568(%rbp), %rax
	movq	-576(%rbp), %rcx
	subq	%rax, %rcx
	movq	%rcx, -576(%rbp)
	jmp	LBB26_5
LBB26_4:
	movq	$0, -576(%rbp)
LBB26_5:
	movq	-528(%rbp), %rax
	movq	-520(%rbp), %rcx
	subq	%rcx, %rax
	movq	%rax, -584(%rbp)
	cmpq	$0, -584(%rbp)
	jle	LBB26_9
## BB#6:
	movq	-512(%rbp), %rax
	movq	-520(%rbp), %rcx
	movq	-584(%rbp), %rdx
	movq	%rax, -256(%rbp)
	movq	%rcx, -264(%rbp)
	movq	%rdx, -272(%rbp)
	movq	-256(%rbp), %rax
	movq	(%rax), %rcx
	movq	96(%rcx), %rcx
	movq	-264(%rbp), %rsi
	movq	-272(%rbp), %rdx
	movq	%rax, %rdi
	callq	*%rcx
	cmpq	-584(%rbp), %rax
	je	LBB26_8
## BB#7:
	leaq	-592(%rbp), %rax
	leaq	-248(%rbp), %rcx
	movq	%rcx, -232(%rbp)
	movq	$-1, -240(%rbp)
	movq	-232(%rbp), %rcx
	movq	-240(%rbp), %rdx
	movq	%rcx, -216(%rbp)
	movq	%rdx, -224(%rbp)
	movq	-216(%rbp), %rcx
	movq	$0, (%rcx)
	movq	-248(%rbp), %rcx
	movq	%rcx, -592(%rbp)
	movq	%rax, -8(%rbp)
	movq	$0, -512(%rbp)
	movq	-512(%rbp), %rax
	movq	%rax, -504(%rbp)
	jmp	LBB26_29
LBB26_8:
	jmp	LBB26_9
LBB26_9:
	cmpq	$0, -576(%rbp)
	jle	LBB26_24
## BB#10:
	xorl	%esi, %esi
	movl	$24, %eax
	movl	%eax, %edx
	leaq	-616(%rbp), %rcx
	movq	-576(%rbp), %rdi
	movb	-545(%rbp), %r8b
	movq	%rcx, -80(%rbp)
	movq	%rdi, -88(%rbp)
	movb	%r8b, -89(%rbp)
	movq	-80(%rbp), %rcx
	movq	-88(%rbp), %rdi
	movb	-89(%rbp), %r8b
	movq	%rcx, -56(%rbp)
	movq	%rdi, -64(%rbp)
	movb	%r8b, -65(%rbp)
	movq	-56(%rbp), %rcx
	movq	%rcx, -48(%rbp)
	movq	-48(%rbp), %rdi
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rdi
	movq	%rdi, %r9
	movq	%r9, -32(%rbp)
	movq	-32(%rbp), %r9
	movq	%rdi, -664(%rbp)        ## 8-byte Spill
	movq	%r9, %rdi
	movq	%rcx, -672(%rbp)        ## 8-byte Spill
	callq	_memset
	movq	-664(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -24(%rbp)
	movq	-24(%rbp), %rcx
	movq	%rcx, -16(%rbp)
	movq	-64(%rbp), %rsi
	movq	-672(%rbp), %rdi        ## 8-byte Reload
	movsbl	-65(%rbp), %edx
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEmc
	leaq	-616(%rbp), %rcx
	movq	-512(%rbp), %rsi
	movq	%rcx, -208(%rbp)
	movq	-208(%rbp), %rcx
	movq	%rcx, -200(%rbp)
	movq	-200(%rbp), %rcx
	movq	%rcx, -192(%rbp)
	movq	-192(%rbp), %rdi
	movq	%rdi, -184(%rbp)
	movq	-184(%rbp), %rdi
	movq	%rdi, -176(%rbp)
	movq	-176(%rbp), %rdi
	movzbl	(%rdi), %eax
	movl	%eax, %edi
	andq	$1, %rdi
	cmpq	$0, %rdi
	movq	%rsi, -680(%rbp)        ## 8-byte Spill
	movq	%rcx, -688(%rbp)        ## 8-byte Spill
	je	LBB26_12
## BB#11:
	movq	-688(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rcx
	movq	%rcx, -120(%rbp)
	movq	-120(%rbp), %rcx
	movq	%rcx, -112(%rbp)
	movq	-112(%rbp), %rcx
	movq	16(%rcx), %rcx
	movq	%rcx, -696(%rbp)        ## 8-byte Spill
	jmp	LBB26_13
LBB26_12:
	movq	-688(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rcx
	movq	%rcx, -160(%rbp)
	movq	-160(%rbp), %rcx
	movq	%rcx, -152(%rbp)
	movq	-152(%rbp), %rcx
	addq	$1, %rcx
	movq	%rcx, -144(%rbp)
	movq	-144(%rbp), %rcx
	movq	%rcx, -136(%rbp)
	movq	-136(%rbp), %rcx
	movq	%rcx, -696(%rbp)        ## 8-byte Spill
LBB26_13:
	movq	-696(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	-576(%rbp), %rcx
	movq	-680(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -280(%rbp)
	movq	%rax, -288(%rbp)
	movq	%rcx, -296(%rbp)
	movq	-280(%rbp), %rax
	movq	(%rax), %rcx
	movq	96(%rcx), %rcx
	movq	-288(%rbp), %rsi
	movq	-296(%rbp), %rdx
Ltmp90:
	movq	%rax, %rdi
	callq	*%rcx
Ltmp91:
	movq	%rax, -704(%rbp)        ## 8-byte Spill
	jmp	LBB26_14
LBB26_14:
	jmp	LBB26_15
LBB26_15:
	movq	-704(%rbp), %rax        ## 8-byte Reload
	cmpq	-576(%rbp), %rax
	je	LBB26_20
## BB#16:
	leaq	-336(%rbp), %rax
	movq	%rax, -320(%rbp)
	movq	$-1, -328(%rbp)
	movq	-320(%rbp), %rax
	movq	-328(%rbp), %rcx
	movq	%rax, -304(%rbp)
	movq	%rcx, -312(%rbp)
	movq	-304(%rbp), %rax
	movq	$0, (%rax)
	movq	-336(%rbp), %rax
	movq	%rax, -712(%rbp)        ## 8-byte Spill
## BB#17:
	leaq	-640(%rbp), %rax
	movq	-712(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -640(%rbp)
	movq	%rax, -344(%rbp)
## BB#18:
	movq	$0, -512(%rbp)
	movq	-512(%rbp), %rax
	movq	%rax, -504(%rbp)
	movl	$1, -644(%rbp)
	jmp	LBB26_21
LBB26_19:
Ltmp92:
	movl	%edx, %ecx
	movq	%rax, -624(%rbp)
	movl	%ecx, -628(%rbp)
Ltmp93:
	leaq	-616(%rbp), %rdi
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev
Ltmp94:
	jmp	LBB26_23
LBB26_20:
	movl	$0, -644(%rbp)
LBB26_21:
	leaq	-616(%rbp), %rdi
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev
	movl	-644(%rbp), %eax
	testl	%eax, %eax
	movl	%eax, -716(%rbp)        ## 4-byte Spill
	je	LBB26_22
	jmp	LBB26_33
LBB26_33:
	movl	-716(%rbp), %eax        ## 4-byte Reload
	subl	$1, %eax
	movl	%eax, -720(%rbp)        ## 4-byte Spill
	je	LBB26_29
	jmp	LBB26_32
LBB26_22:
	jmp	LBB26_24
LBB26_23:
	jmp	LBB26_30
LBB26_24:
	movq	-536(%rbp), %rax
	movq	-528(%rbp), %rcx
	subq	%rcx, %rax
	movq	%rax, -584(%rbp)
	cmpq	$0, -584(%rbp)
	jle	LBB26_28
## BB#25:
	movq	-512(%rbp), %rax
	movq	-528(%rbp), %rcx
	movq	-584(%rbp), %rdx
	movq	%rax, -360(%rbp)
	movq	%rcx, -368(%rbp)
	movq	%rdx, -376(%rbp)
	movq	-360(%rbp), %rax
	movq	(%rax), %rcx
	movq	96(%rcx), %rcx
	movq	-368(%rbp), %rsi
	movq	-376(%rbp), %rdx
	movq	%rax, %rdi
	callq	*%rcx
	cmpq	-584(%rbp), %rax
	je	LBB26_27
## BB#26:
	leaq	-656(%rbp), %rax
	leaq	-416(%rbp), %rcx
	movq	%rcx, -400(%rbp)
	movq	$-1, -408(%rbp)
	movq	-400(%rbp), %rcx
	movq	-408(%rbp), %rdx
	movq	%rcx, -384(%rbp)
	movq	%rdx, -392(%rbp)
	movq	-384(%rbp), %rcx
	movq	$0, (%rcx)
	movq	-416(%rbp), %rcx
	movq	%rcx, -656(%rbp)
	movq	%rax, -424(%rbp)
	movq	$0, -512(%rbp)
	movq	-512(%rbp), %rax
	movq	%rax, -504(%rbp)
	jmp	LBB26_29
LBB26_27:
	jmp	LBB26_28
LBB26_28:
	movq	-544(%rbp), %rax
	movq	%rax, -432(%rbp)
	movq	$0, -440(%rbp)
	movq	-432(%rbp), %rax
	movq	24(%rax), %rcx
	movq	%rcx, -448(%rbp)
	movq	-440(%rbp), %rcx
	movq	%rcx, 24(%rax)
	movq	-512(%rbp), %rax
	movq	%rax, -504(%rbp)
LBB26_29:
	movq	-504(%rbp), %rax
	addq	$736, %rsp              ## imm = 0x2E0
	popq	%rbp
	retq
LBB26_30:
	movq	-624(%rbp), %rdi
	callq	__Unwind_Resume
LBB26_31:
Ltmp95:
	movl	%edx, %ecx
	movq	%rax, %rdi
	movl	%ecx, -724(%rbp)        ## 4-byte Spill
	callq	___clang_call_terminate
LBB26_32:
Lfunc_end5:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table26:
Lexception5:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.asciz	"\274"                  ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.byte	52                      ## Call site table length
Lset94 = Lfunc_begin5-Lfunc_begin5      ## >> Call Site 1 <<
	.long	Lset94
Lset95 = Ltmp90-Lfunc_begin5            ##   Call between Lfunc_begin5 and Ltmp90
	.long	Lset95
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset96 = Ltmp90-Lfunc_begin5            ## >> Call Site 2 <<
	.long	Lset96
Lset97 = Ltmp91-Ltmp90                  ##   Call between Ltmp90 and Ltmp91
	.long	Lset97
Lset98 = Ltmp92-Lfunc_begin5            ##     jumps to Ltmp92
	.long	Lset98
	.byte	0                       ##   On action: cleanup
Lset99 = Ltmp93-Lfunc_begin5            ## >> Call Site 3 <<
	.long	Lset99
Lset100 = Ltmp94-Ltmp93                 ##   Call between Ltmp93 and Ltmp94
	.long	Lset100
Lset101 = Ltmp95-Lfunc_begin5           ##     jumps to Ltmp95
	.long	Lset101
	.byte	1                       ##   On action: 1
Lset102 = Ltmp94-Lfunc_begin5           ## >> Call Site 4 <<
	.long	Lset102
Lset103 = Lfunc_end5-Ltmp94             ##   Call between Ltmp94 and Lfunc_end5
	.long	Lset103
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__ZNSt3__111char_traitsIcE6lengthEPKc ## -- Begin function _ZNSt3__111char_traitsIcE6lengthEPKc
	.weak_definition	__ZNSt3__111char_traitsIcE6lengthEPKc
	.p2align	4, 0x90
__ZNSt3__111char_traitsIcE6lengthEPKc:  ## @_ZNSt3__111char_traitsIcE6lengthEPKc
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi78:
	.cfi_def_cfa_offset 16
Lcfi79:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi80:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	_strlen
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	" "

	.section	__DATA,__data
	.globl	_x                      ## @x
	.p2align	2
_x:
	.long	2                       ## 0x2


.subsections_via_symbols
