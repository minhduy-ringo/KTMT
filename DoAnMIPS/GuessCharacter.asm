.text

.globl GuessChar

# How to call
# $a0: player input
# $a1: word
# $a2: word length
# $a3: word pseudo
# jal GuessChar

GuessChar:
	# Save return address $ra
	subu	$sp, $sp, 4
	sw 	$ra, ($sp)

	# $a0: player input
	# $a1: word
	# $a2: word length
	# $a3: word pseudo
	# return in $v0: 0 if wrong, n if corerct with n equal number of time the character appear in the word

	li	$t0, 0	# Khoi tao bien dem
	li 	$t1, 0	# Luu so ki tu xuat hien
	move	$t3, $a2
	
CheckCharacter:
	# Check loop condition
	beq 	$t0, $t3, GoExit
	# Loop through each character in the string, compare to pseudo if this position is guessed yet or not
	# If char was already guessed, skip this char
	lb	$t2, ($a3)
	bne	$t2, '*', CheckCharacter.Skip
	# Else check if input char is corresponding to char positioned in string
	lb	$t2, ($a1)
	beq 	$a0, $t2, CheckCharacter.IncScore
CheckCharacter.Skip:
	addi	$a1, $a1, 1
	addi	$a3, $a3, 1
	addi 	$t0, $t0, 1
	j 	CheckCharacter

CheckCharacter.IncScore:
	addi 	$t0, $t0, 1
	addi	$t1, $t1, 1
	sb	$t2, ($a3)
	addi	$a1, $a1, 1
	addi	$a3, $a3, 1
	j 	CheckCharacter
	
GoExit:
	# Restore $ra
	lw 	$ra, ($sp)
	addi	$sp, $sp, 4
	la 	$v0, ($t1)
	jr 	$ra
	
