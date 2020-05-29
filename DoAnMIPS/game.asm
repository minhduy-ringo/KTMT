.data
winMsg:		.asciiz "You win!\n"
loseMsg:	.asciiz "You lose\n"
scoreMsg:	.asciiz "Your score: "
guessPromt1:	.asciiz "Guess 1.A character / 2. Word ? "
guessPromt2:	.asciiz "Your guess: "
afterWinPromt:	.asciiz "1. Continue / 2. Exit to menu ? "
afterLosePromt: .asciiz "1. Play again / 2. Exit to menu ? " 
breakBar:	.asciiz "==========================================\n"

score:		.word 0
pseudoWord:	.space 255
guessInput:	.space 255

.text
.globl Game
Game:
	# Save $ra return address to main
	subu 	$sp, $sp, 4
	sw 	$ra, ($sp)
	# Save player name from $a0 to $s0
	move 	$s0, $a0
Game.Init:
	# reserve $s1 for score for each round
	# reserve $s2 for word
	# reserve $s3 for word pseudo
	# reserve $s4 for word length
	# reserve $s5 for error
	li 	$s1, 0
	jal 	ReadWordFile
	move 	$s2, $v0
	move 	$s4, $v1
	
	la 	$s3, pseudoWord
	li 	$t0, 0
	li 	$t1, '*'
CreatePseudo:
	sb 	$t1, 0($s3)
	addi 	$s3, $s3, 1
	addi 	$t0, $t0, 1
	bne 	$t0, $s4, CreatePseudo

GameProcess:
	# Print word pseudo
	li 	$v0, 4
	la 	$a0, pseudoWord
	syscall
	li 	$v0, 11
	li 	$a0, 10
	syscall

	# Print guess promt
	li 	$v0, 4
	la 	$a0, guessPromt1
	syscall
	li 	$v0, 5
	syscall
	
	# Check user input and call GuessWord or GuessChar function
	beq $v0, 1, GoGuessChar
	beq $v0, 2, GoGuessWord

GoGuessChar:
	# $a0: player input
	# $a1: word
	# $a2: word length
	# $a3: word pseudo
	# return in $v0: 0 if wrong, n if corerct with n equal number of time the character appear in the word

	# Take player guess
	li 	$v0, 4
	la 	$a0, guessPromt2
	syscall
	li 	$v0, 12
	syscall
	move	$t0, $v0
	li 	$v0, 11
	li 	$a0, 10
	syscall

	la	$a0, ($t0)
	la 	$a1, ($s2)
	la 	$a2, ($s4)
	la 	$a3, pseudoWord
	jal 	GuessChar

	# Check return
	beq 	$v0, 0, GuessChar.Wrong
GuessChar.Correct:
	# inc round score
	add 	$s1, $s1, $v0
	beq 	$s1, $s4, WinScreen
	j 	GameProcess
GuessChar.Wrong:
	# Inc error
	addi 	$s5, $s5, 1
	# Call draw
	move 	$a0, $s5
	#jal	DrawHangMan
	beq 	$s5, 7, LoseScreen
	j 	GameProcess

GoGuessWord:
	# $a0: player input
	# $a1: word
	# $a2: word length
	# return: $v0 result

	# Take player guess
	li 	$v0, 4
	la 	$a0, guessPromt2
	syscall
	li 	$v0, 8
	la 	$a0, guessInput
	syscall

	la 	$a0, guessInput
	la 	$a1, ($s2)
	la 	$a2, ($s4)
	#jal	GuessWord
	
	beq 	$v0, 0, LoseScreen
	beq 	$v0, 1, WinScreen
	
WinScreen:
	# Add score
	la 	$t0, score
	add 	$t0, $t0, $s1
	# Print win message
	li 	$v0, 4
	la 	$a0, winMsg
	syscall
	# Print score
	li 	$v0, 4
	la 	$a0, scoreMsg
	syscall
	li 	$v0, 1
	la 	$a0, score
	syscall
	# Print win promt
	li 	$v0, 4
	la 	$a0, afterWinPromt
	syscall
	# Get input
	li 	$v0, 5
	syscall
	beq 	$v0, 1, Game.Init
	beq 	$v0, 2, Win.ExitToMenu
	
LoseScreen:
	# Save player score to file
	move 	$a0, $s0
	move 	$a1, $s1
	jal 	WriteFile
	# Print lose message
	li 	$v0, 4
	la 	$a0, loseMsg
	syscall
	# Print score
	li 	$v0, 4
	la 	$a0, scoreMsg
	syscall
	li 	$v0, 1
	la 	$a0, ($s1)
	syscall
	# Draw hang man
	li 	$a0, 7
	#jal 	DrawHangMan
	# Print lose promt
	li 	$v0, 4
	la 	$a0, afterLosePromt
	syscall
	li 	$v0, 5
	syscall
	beq 	$v0, 1, Game.Init
	beq 	$v0, 2, Lose.ExitToMenu

Win.ExitToMenu:
	# Save player score to file
	move 	$a0, $s0
	move 	$a1, $s1
	jal 	WriteFile

	lw 	$ra, ($sp)
	addu 	$sp, $sp, 4
	jr 	$ra
Lose.ExitToMenu:
	lw 	$ra, ($sp)
	addu 	$sp, $sp, 4
	jr 	$ra
