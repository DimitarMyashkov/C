	.file	"transformation.c"
	.text
	.def	is_valid;	.scl	3;	.type	32;	.endef
	.seh_proc	is_valid
is_valid:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$45, %al
	je	.L2
	movq	16(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$43, %al
	jne	.L3
.L2:
	addq	$1, 16(%rbp)
.L3:
	movq	16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L6
	movl	$0, %eax
	jmp	.L5
.L8:
	movq	16(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	subl	$48, %eax
	cmpl	$9, %eax
	jbe	.L7
	movl	$0, %eax
	jmp	.L5
.L7:
	addq	$1, 16(%rbp)
.L6:
	movq	16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L8
	movl	$1, %eax
.L5:
	popq	%rbp
	ret
	.seh_endproc
	.globl	transform_string_to_long
	.def	transform_string_to_long;	.scl	2;	.type	32;	.endef
	.seh_proc	transform_string_to_long
transform_string_to_long:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$152, %rsp
	.seh_stackalloc	152
	leaq	144(%rsp), %rbp
	.seh_setframe	%rbp, 144
	.seh_endprologue
	movq	%rcx, 32(%rbp)
	movq	%rdx, 40(%rbp)
	movq	40(%rbp), %rax
	movq	%rax, %rcx
	call	is_valid
	testb	%al, %al
	je	.L10
	movq	40(%rbp), %rax
	movl	$10, %r8d
	movl	$0, %edx
	movq	%rax, %rcx
	call	strtol
	movl	%eax, -112(%rbp)
	movb	$0, -108(%rbp)
	jmp	.L11
.L10:
	movl	$0, -112(%rbp)
	leaq	-112(%rbp), %rax
	addq	$4, %rax
	movabsq	$2334106421097295433, %rdx
	movabsq	$8391086215279963753, %rcx
	movq	%rdx, (%rax)
	movq	%rcx, 8(%rax)
	movabsq	$29113321772053280, %rbx
	movq	%rbx, 13(%rax)
.L11:
	movq	32(%rbp), %rax
	movq	-112(%rbp), %rcx
	movq	-104(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	-16(%rbp), %rdx
	movq	%rdx, 96(%rax)
	movq	32(%rbp), %rax
	addq	$152, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 13.1.0"
	.def	strtol;	.scl	2;	.type	32;	.endef
