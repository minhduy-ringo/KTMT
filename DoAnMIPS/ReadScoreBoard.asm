.data
sb_path:	.asciiz "scoreboard.txt"

fileBuffer:	.space 1000

arrayStart:	.space 32

.text

.globl ReadScoreBoard

# How to call
# $a0 = mode
# jal ReadScoreBoard

ReadScoreBoard:
	# Read 10 player with highest score in "ScoreBoard" file into array and return address of first index
	# Mode: 0 if not write to screen, 1 if write to screen

	# Save return address $ra, $s0
	subu 	$sp, $sp, 4
	sw 	$ra, ($sp)
	move 	$t9, $a0

	# Open input file with path from input_file_path
	# Flags $a1 = 0, open for read
	# Mode $a2 = 0, ignore
	li 	$v0, 13
	la 	$a0, sb_path
	li 	$a1, 0
	li 	$a2, 0
	syscall
	move 	$t8, $v0	# Save the file descriptor

ReadIntoBuffer:
	move	$a0, $t8
	la	$a1, fileBuffer
	li	$a2, 1000
	li	$v0, 14
	syscall
	bltz	$v0, Exit
	#beq	$v0, 0, 
	
	li	$t3, 0
	la	$t0, fileBuffer
	la	$t1, arrayStart
LoopBuffer:
	addi	$t3, $t3, 1
	li	$t4, 32
	beq	$t3, 10, LoopBuffer.Exit
ReadName:
	lb	$t2, ($t0)
	sb	$t2, ($t1)
	addi	$t0, $t0, 1
	addi	$t1, $t1, 1
	subi	$t4, $t4, 1
	beq	$t2, ' ', ReadScore
	j 	ReadName
ReadScore:
	lb	$t2, ($t0)
	sb	$t2, ($t1)
	addi	$t0, $t0, 1
	addi	$t1, $t1, 1
	subi	$t4, $t4, 1
	beq	$t2, ' ', ReadRound
	j 	ReadScore
ReadRound:
	lb	$t2, ($t0)
	sb	$t2, ($t1)
	addi	$t0, $t0, 1
	addi	$t1, $t1, 1
	subi	$t4, $t4, 1
	beq	$t2, 10, LoopBuffer.IncIndex
	j 	ReadRound
LoopBuffer.IncIndex:
	add 	$t1, $t1, $t4
	j	LoopBuffer
LoopBuffer.Exit:
	bne	$t9, 1, Exit
	
	la	$a0, arrayStart
	li	$t0, 0
	li	$v0, 4
WriteToScreen:
	syscall
	addi	$a0, $a0, 32
	addi	$t0, $t0, 1
	bne	$t0, 10, WriteToScreen
	
Exit:
	# Restore $ra, $s0
	lw 	$ra, ($sp)
	addu	$sp, $sp, 4

	# Close file
	li 	$v0, 16
	move 	$a0, $t8
	syscall
	
	la	$v0, arrayStart
	jr	$ra

	
