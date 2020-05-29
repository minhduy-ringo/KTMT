.text
.globl GuessChar
GuessChar:
	# Save return address $ra
	subu	$sp, $sp, 4
	sw 	$ra, ($sp)

	# $a0: player input
	# $a1: word
	# $a2: word length
	# $a3: word pseudo
	# return in $v0: 0 if wrong, n if corerct with n equal number of time the character appear in the word

	li	$t0, 1	# Khoi tao bien dem
	li 	$t1, 0	# Luu so ki tu xuat hien
	
CheckCharacter:
	# Kiem tra dieu kien lap
	beq 	$t0, $a2, GoExit
	# Kiem tra ki tu 
	lb	$t2, ($a1)
	beq 	$a0, $t2, CheckCharacter.IncScore
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
	la 	$v0, ($t1)
	jr 	$ra
	
