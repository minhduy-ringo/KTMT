.data
input_file_path: .asciiz "dethi.txt"
n:		 .word 144
chr:		 .space 8
word:		 .space 255

.text

.globl ReadFile
ReadFile:
	# Save return address $ra, $s0
	subu $sp, $sp, 8
	sw $ra, 4($sp)
	sw $s0, 0($sp)

	# Open input file with path from input_file_path
	# Flags $a1 = 0, open for read
	# Mode $a2 = 0, ignore
	li $v0, 13
	la $a0, input_file_path
	li $a1, 0
	li $a2, 0
	syscall
	move $t8, $v0	# Save the file descriptor

	# Random a number
	jal Random
	move $t7, $a0

	# Argument to read file
	# $a0, file descript
	# $a1, input buffer chr
	# $a2, 1 to read each character
	move $a0, $t8
	la $a1, chr
	li $a2, 1

	# Read
	la $s0, word
	bne $t7, 1, Read

ReadFirst:
	li $v0, 14
	syscall
	lb $t0, 0($a1)
	beq $t0, '*', EndRead
	sb $t0, 0($s0)
	addi $s0, $s0, 1
	j ReadFirst

Read:	
	li $t1, 1 	# Count number of word readed
	jal LoopToWord
RRead:
	li $v0, 14
	syscall
	lb $t0, 0($a1)
	beq $t0, '*', EndRead
	sb $t0, 0($s0)
	addi $s0, $s0, 1
	j RRead

LoopToWord:
	# Read char
	li $v0, 14
	syscall
	lb $t0, 0($a1)
	bne $t0, '*', NInc
Inc:
	addi $t1, $t1, 1
NInc:
	beq $t1, $t7, EndLTW  # if count = n
	j LoopToWord
EndLTW:
	jr $ra
EndRead:
	sb $zero, 0($s0) # Add null-terminate 
	j ExitReadFile

ExitReadFile:
	# Close file
	li $v0, 16
	move $a0, $t8
	syscall

	# Restore $ra, $s0
	lw $s0, ($sp)
	addu $sp, $sp, 4
	lw $ra, ($sp)

	# Save word to $v0 to return
	la $v0, word
	
	jr $ra

####### Random an integer number from 0 to N and return to $sa0
Random:
	lw $a1, n
	li $v0, 42
	syscall
	beq $a0, 0, Random
	jr $ra
