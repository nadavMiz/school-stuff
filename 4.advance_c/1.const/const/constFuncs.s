	.file	"constFuncs.c"
	.text
	.globl	StrLen
	.type	StrLen, @function
StrLen:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$1, -4(%ebp)
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	movb	%al, -5(%ebp)
	cmpl	$0, 8(%ebp)
	jne	.L4
	movl	$0, %eax
	jmp	.L3
.L5:
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movb	%al, -5(%ebp)
	addl	$1, -4(%ebp)
.L4:
	cmpb	$0, -5(%ebp)
	jne	.L5
	movl	-4(%ebp), %eax
	subl	$1, %eax
.L3:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	StrLen, .-StrLen
	.globl	StrLenRecHelper
	.type	StrLenRecHelper, @function
StrLenRecHelper:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L7
	movl	$0, %eax
	jmp	.L8
.L7:
	movl	8(%ebp), %eax
	addl	$1, %eax
	subl	$12, %esp
	pushl	%eax
	call	StrLenRecHelper
	addl	$16, %esp
	addl	$1, %eax
.L8:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	StrLenRecHelper, .-StrLenRecHelper
	.globl	StrLenRec
	.type	StrLenRec, @function
StrLenRec:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	cmpl	$0, 8(%ebp)
	jne	.L10
	movl	$0, %eax
	jmp	.L11
.L10:
	subl	$12, %esp
	pushl	8(%ebp)
	call	StrLenRecHelper
	addl	$16, %esp
.L11:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	StrLenRec, .-StrLenRec
	.section	.rodata
.LC0:
	.string	"bloop"
.LC1:
	.string	"length: %d\n"
.LC2:
	.string	"length rec: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
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
	subl	$20, %esp
	movl	$.LC0, -12(%ebp)
	pushl	-12(%ebp)
	call	StrLen
	addl	$4, %esp
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	subl	$12, %esp
	pushl	-12(%ebp)
	call	StrLenRec
	addl	$16, %esp
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
