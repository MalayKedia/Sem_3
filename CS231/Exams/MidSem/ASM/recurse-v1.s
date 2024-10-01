.text

recurse:
	# Stack manipulation here
	# Save as caller: t0
	# Save as callee: ra
	lw	$t0, 0($sp)	# get additional arg in t0
	addi	$sp, $sp, -8
	sw	$ra, 4($sp)
	sw	$t0, 0($sp)

	# m in a0, n in t0

	slt	$t1, $0, $a0
	beq	$t1, $0, BASECASE # if !(0 < m)
	slt	$t1, $0, $t0
	beq	$t1, $0, BASECASE # if !(0 < n)

	# Non-base case
	andi	$t1, $a0, 0x1		# t1 = m%2
	beq	$t1, $0, IFCASE1	# if ((m%2) == 0)

	ELSECASE:
	# prepare n in stack
	addi	$sp, $sp, -4
	addi	$t1, $t0, -1
	sw	$t1, 0($sp)
	jal	recurse		# no need to change m
	addi	$sp, $sp, 4
	lw	$t0, 0($sp)	# restore my n
	add	$v0, $v0, $t0	# new ret val += n
	j	RET

	IFCASE1:
	# prepare n in stack
	addi	$sp, $sp, -4
	sw	$t0, 0($sp)
	srl	$a0, $a0, 1	# new m is m/2
	jal	recurse
	addi	$sp, $sp, 4
	addi	$v0, $v0, 1	# this is the new return value
	j	RET

	BASECASE:
	addi	$v0, $0, 0

	RET:
	# Restore stack
	lw	$ra, 4($sp)
	addi	$sp, $sp, 8
	jr	$ra

main:
	# Stack manipulation
	# Save as callee: $ra
	addi	$sp, $sp, -4
	sw	$ra, 0($sp)

	# read in m
	li	$v0, 5
	syscall
	move 	$a0, $v0
	# read in n
	li	$v0, 5
	syscall
	move 	$t0, $v0

	# prepare n in stack
	addi	$sp, $sp, -4
	sw	$t0, 0($sp)
	jal	recurse
	addi	$sp, $sp, 4

	# print return value
	move	$a0, $v0
	li	$v0, 1
	syscall

	# Stack manipulation
	lw	$ra, 0($sp)
	addi	$sp, $sp, 4
	jr	$ra

