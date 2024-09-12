# Sample spim program
#
# Written by Pat Troy, 11/8/2002

	.data
prompt:	.asciiz "Enter in an integer: "
str1:	.asciiz "the answer is: "
newline: .asciiz	"\n"
bye:	.asciiz	"Goodbye!\n"
	.globl	main
	
	.text
main:

	# initialize 
	li	$s0, 10
	
	# prompt for input
	li	$v0, 4
	la	$a0, prompt
	syscall

	# read in the value
	li	$v0, 5
	syscall
	move 	$s0, $v0

	
loop:	
	# print str1
	li	$v0, 4
	la	$a0, str1
	syscall

	# print loop value
	li	$v0, 1
	move	$a0, $s0
	syscall

	# print newline
	li	$v0, 4
	la	$a0, newline
	syscall

	# decrement loop value and branch if not negative
	sub	$s0, $s0, 1
	bgez	$s0, loop

	# print goodbye message
	li	$v0, 4
	la	$a0, bye
	syscall



