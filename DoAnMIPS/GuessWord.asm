.text

.globl GuessWord

# How to call
# $a0: player input
# $a1: word
# $a2: word length
# jal GuessWord

GuessWord:
	# Save $ra return address to main
	subu 	$sp, $sp, 4
	sw 	$ra, ($sp)

	# $a0: player input
	# $a1: word
	# $a2: word length
	# return: $v0 = 0 if wrong ? 1 if correct

	move 	$t0, $a0
	move	$t1, $a1
	move	$t2, $a2
	li	$v0, 0

	# Check user input string length
	# $t8: counter
	li	$t8, 0
	move	$t3, $a0
StrLength:
	lb 	$t4, 0($t3)
	beq 	$t4, $zero, sLengthEnd
	beq 	$t4, 10, sLengthEnd
	addi 	$t8, $t8, 1
	addi 	$t3, $t3, 1
	j 	StrLength
sLengthEnd:

	# If user string input length > word length => wrong
	bne	$a2, $t8, ExitGuessWord
	# Else loop through each character from both string and compare
	li	$t8, 0	# Counter
Check:
	beq	$t8, $a2, Check.Correct	# If end of string, return correct
	lb	$t3, ($t0)	# Get char from user input
	lb	$t4, ($t1)	# Get char from word
	bne	$t3, $t4, ExitGuessWord	# Compare if two char is alike
	addi	$t0, $t0, 1	# Next char
	addi	$t1, $t1, 1
	addi	$t8, $t8, 1	# Inc counter
	j 	Check

Check.Correct:
	li	$v0, 1
	j	ExitGuessWord

ExitGuessWord:
	lw	$ra, ($sp)
	addu	$sp, $sp, 4
	jr	$ra	
