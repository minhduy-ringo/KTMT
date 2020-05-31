.data
output_file_path: .asciiz "./nguoichoi.txt"
space:		  .asciiz " "
line_break:	  .asciiz "\n"

score:		  .space 10
round:		  .space 10
.text
.globl WriteFile

# How to call
# $a0 = player's name
# $a1 = player's score
# $a2 = player's round win
# jal WriteFile

WriteFile:
	# Save return address $ra, $s0, $s1, $s2
	subu 	$sp, $sp, 12
	sw 	$ra, ($sp)
	sw	$s0, 4($sp)
	sw	$s1, 8($sp)
	sw	$s2, 12($sp)

	move 	$s0, $a0	# name
	move 	$s1, $a1	# score
	move 	$s2, $a2	# round

	# Open output file with path from output_file_path and write combined string
	# Flags $a1 = 9, create and append
	# Mode $a2 = 0, ignore
	li 	$v0, 13
	la 	$a0, output_file_path
	li 	$a1, 9
	li 	$a2, 0
	syscall
	move 	$t8, $v0	# Save the file descriptor
	
	# Count player name length
	li 	$v0, 0
	move 	$a0, $s0
	jal 	StrLength
	move	$t0, $v0

	# Write player name into file
	li 	$v0, 15
	move 	$a0, $t8
	move 	$a1, $s0
	move 	$a2, $t0
	syscall

	# Write a space
	li 	$v0, 15
	move 	$a0, $t8
	la 	$a1, space
	la 	$a2, 1
	syscall

	# Convert score to string
	la	$v0, score
	li	$v1, 0
	move 	$a0, $s1
	jal 	IntToStr

	# Write player score into file
	li 	$v0, 15
	move 	$a0, $t8
	la	$a1, score
	move 	$a2, $v1
	syscall

	# Write a space
	li 	$v0, 15
	move 	$a0, $t8
	la 	$a1, space
	la 	$a2, 1
	syscall

	# Convert round to string
	la	$v0, round
	li	$v1, 0
	move	$a0, $s2
	jal 	IntToStr

	# Write player round into file
	li 	$v0, 15
	move 	$a0, $t8
	la	$a1, round
	move 	$a2, $v1
	syscall

	# Line break
	li 	$v0, 15
	move 	$a0, $t8
	la 	$a1, line_break
	la 	$a2, 1
	syscall

	# Close file
	li 	$v0, 16
	move 	$a0, $t8
	syscall

	j ExitWriteFile

ExitWriteFile:
	lw 	$ra, ($sp)
	addu 	$sp, $sp, 4
	lw	$s0, ($sp)
	addu 	$sp, $sp, 4
	lw	$s1, ($sp)
	addu 	$sp, $sp, 4
	lw	$s2, ($sp)
	addu 	$sp, $sp, 4
	jr 	$ra

#	Calculate result string length to $t7
#	In: $a0: string
#	Out: $t7 length
StrLength:
	lb 	$t0, 0($a0)
	beq 	$t0, $zero, sLengthEnd
	beq 	$t0, 10, sLengthEnd
	addi 	$v0, $v0, 1
	addi 	$a0, $a0, 1
	j 	StrLength
sLengthEnd:
	jr 	$ra

#	Int to string convert
#	Input: $a0 = int
#	Output: $v0 = string, $v1 = string length
IntToStr:
	div	$a0, $a0, 10
	mfhi	$t0
	addi	$t0, $t0, 48	# convert to ascii
	subu	$sp, $sp, 1
	sb	$t0, ($sp)
	addi	$v1, $v1, 1
	li	$t1, 0
	beqz	$a0, IntToStr.Reverse
	j	IntToStr
IntToStr.Reverse:
	lb	$t0, ($sp)
	addu	$sp, $sp, 1
	sb	$t0, ($v0)
	addi	$v0, $v0, 1
	addi	$t1, $t1, 1
	bne	$t1, $v1, IntToStr.Reverse
	jr 	$ra
