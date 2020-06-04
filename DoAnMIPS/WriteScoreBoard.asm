.data
sb_path:	.asciiz "scoreboard.txt"

score:		.space 8
.text

.globl WriteScoreBoardFile

# How to call
# $a0: player string ( name score round )
# $a1: player' score (int)
# jal WriteScoreBoardFile

WriteScoreBoardFile:
	# Save return address $ra, $s0, $s1, $s2
	subu 	$sp, $sp, 16
	sw	$ra, ($sp)
	sw	$s0, 4($sp)
	sw	$s1, 8($sp)
	sw	$s2, 12($sp)

	move	$s0, $a0	# string
	move	$s1, $a1	# score
	
	li	$a0, 0
	jal	ReadScoreBoard
	move	$s2, $v0

	# Open output file with path from sb_path and write combined string
	# Flags $a1 = 1
	# Mode $a2 = 0, ignore
	li 	$v0, 13
	la 	$a0, sb_path
	li 	$a1, 1
	li 	$a2, 0
	syscall
	move 	$t8, $v0	# Save the file descriptor
	
	li	$t1, 0		# counter
EachPlayerLoop:
	addi	$t1, $t1, 1
	beq	$t1, 10, Exit
	la	$t9, score
	move	$t0, $s2
LoopName:
	lb	$t2, ($t0)
	addi	$t0, $t0, 1
	beq	$t2, ' ', ReadScore
	j	LoopName
ReadScore:
	lb	$t2, ($t0)
	sb	$t2, ($t9)
	beq	$t2, ' ', StrToInt.Init
	addi	$t0, $t0, 1
	addi	$t9, $t9, 1
	j	ReadScore
StrToInt.Init:
	la	$t9, score
	li	$t3, 0
	li	$t4, 10
StrToInt:
	lb	$t5, ($t9)
	beq	$t5, ' ', StrToInt.Exit
	addi	$t5, $t5, -48
	mul	$t3, $t3, $t4
	add	$t3, $t3, $t5
	addi	$t9, $t9, 1
	j	StrToInt
StrToInt.Exit:
	blt	$t3, $s1, Replace
	li 	$v0, 15
	move 	$a0, $t8
	move 	$a1, $s2
	li	$a2, 32
	syscall
	addi	$s2, $s2, 32
	j	EachPlayerLoop

Replace:
	li 	$v0, 15
	move 	$a0, $t8
	move 	$a1, $s0
	li	$a2, 32
	syscall
	li	$t3, 10
	subu	$t1, $t3, $t1
Loop:
	beq	$t1, 0, Exit

	li 	$v0, 15
	move 	$a0, $t8
	move 	$a1, $s2
	li	$a2, 32
	syscall

	addi	$s2, $s2, 32
	subi	$t1, $t1, 1
	j Loop

Exit:
	lw 	$ra, ($sp)
	addu 	$sp, $sp, 4
	lw	$s0, ($sp)
	addu 	$sp, $sp, 4
	lw	$s1, ($sp)
	addu 	$sp, $sp, 4
	lw	$s2, ($sp)
	addu 	$sp, $sp, 4
	jr 	$ra
	