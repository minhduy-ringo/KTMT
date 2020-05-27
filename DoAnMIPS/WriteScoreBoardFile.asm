.data
output_file_path: .asciiz "./nguoichoi.txt"
teststr1:	  .asciiz "playername"
teststr2:	  .asciiz "score"
space:		  .asciiz " "
line_break:	  .asciiz "\n"
.text
.globl WriteFile

# How to call
# $a0 = player's name
# $a1 = player's score
# jal WriteFile

WriteFile:
	# Save return address $ra, $s0
	subu $sp, $sp, 8
	sw $ra, 4($sp)
	sw $s0, 0($sp)

	# For test, delete this after debug
	# la $a0, teststr1
	# la $a1, teststr2

	move $t0, $a0
	move $t1, $a1

	# Open output file with path from output_file_path and write combined string
	# Flags $a1 = 9, create and append
	# Mode $a2 = 0, ignore
	li $v0, 13
	la $a0, output_file_path
	li $a1, 9
	li $a2, 0
	syscall
	move $t8, $v0	# Save the file descriptor
	
	# Count player name length
	li $t7, 0
	la $s0, ($t0)
	jal StrLength

	# Write player name into file
	li $v0, 15
	move $a0, $t8
	la $a1, ($t0)
	la $a2, ($t7)
	syscall

	# Write a space
	li $v0, 15
	move $a0, $t8
	la $a1, space
	la $a2, 1
	syscall

	# Count player score length
	li $t7, 0
	la $s0, ($t1)
	jal StrLength

	# Write player score into file
	li $v0, 15
	move $a0, $t8
	la $a1, ($t1)
	la $a2, ($t7)
	syscall

	# Line break
	li $v0, 15
	move $a0, $t8
	la $a1, line_break
	la $a2, 1
	syscall

	# Close file
	li $v0, 16
	move $a0, $t8
	syscall

	j ExitWriteFile

ExitWriteFile:
	lw $s0, ($sp)
	addu $sp, $sp, 4
	lw $ra, ($sp)
	jr $ra

####### Determine result string length to $t7
StrLength:
	lb $t2, 0($s0)
	beq $t2, $zero, sLengthEnd
	addi $t7, $t7, 1
	addi $s0, $s0, 1
	j StrLength
sLengthEnd:
	jr $ra





####### Add two string together
	# IN: string $a0, string $a1; OUT: string $s0	
Strcpy:
	# la $s0, output
	li $t8, 10
CopyFirst:
	lb $t0, 0($a0)
	beq $t0, $zero, CopyAsteris
	beq $t0, $t8, CopyAsteris
	sb $t0, 0($s0)
	addi $a0, $a0, 1
	addi $s0, $s0, 1
	j CopyFirst
CopyAsteris:
	li $t0, ' '
	sb $t0, 0($s0)
	addi $s0, $s0, 1
CopySecond:
	lb $t0, 0($a1)
	beq $t0, $zero, EndStrcpy
	beq $t0, $t8, EndStrcpy
	sb $t0, 0($s0)
	addi $a1, $a1, 1
	addi $s0, $s0, 1
	j CopySecond
EndStrcpy:
	# Add null terminate
	sb $zero, 0($s0)
	jr $ra