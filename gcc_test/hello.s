	.file	"hello.c"
	.section	.rodata
.LC0:
	.string	"#if 1"
.LC1:
	.string	"15:26:59"
.LC2:
	.string	"May  5 2020"
	.align 8
.LC3:
	.string	"This program complied on %s:%s\n"
.LC4:
	.string	"Hello Word!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$.LC0, %edi
	call	puts
	call	test
	movl	$.LC1, %edx
	movl	$.LC2, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC4, %edi
	call	puts
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
.LC5:
	.string	"hello.c"
	.align 8
.LC6:
	.string	"The func  is using into %s:%d%s()\n"
	.text
	.globl	test
	.type	test, @function
test:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$__FUNCTION__.2352, %ecx
	movl	$33, %edx
	movl	$.LC5, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	test, .-test
	.section	.rodata
	.type	__FUNCTION__.2352, @object
	.size	__FUNCTION__.2352, 5
__FUNCTION__.2352:
	.string	"test"
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.4) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
