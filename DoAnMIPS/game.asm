.data
winMsg:		.asciiz "You win!\n"
loseMsg:	.asciiz "You lose\n"
scoreMsg:	.asciiz "Your score: "
guessPromt:	.asciiz "Guess 1.A character / 2. Word ? "
afterWinPromt:	.asciiz "1. Continue / 2. Exit to menu ? "
afterLosePromt: .asciiz "1. Play again / 2. Exit to menu ? " 
breakBar:	.asciiz "=====================================\n"

error:		.word 0
gameState:	.byte 0	 	# To check which state the game is in
				# 0: win, 1: lose
pseudoWord:	.space 255

.text
.globl Game
Game:
	# Save $ra return address to main
	subu $sp, $sp, 4
	sw $ra, ($sp)

	# Save player name from $a0 to $s0
	# Save player score from $a1 to $s1
	# reserve $s2 for word
	# reserve $s3 for word pseudo
	# reserve $s4 for word length
	move $s0, $a0

	jal ReadWordFile
	move $s2, $v0
	move $s4, $v1
	la $s3, pseudoWord

	li $t0, 1
	li $t1, '*'
CreatePseudo:
	sb $t1, 0($s3)
	addi $s3, $s3, 1
	addi $t0, $t0, 1
	bne $t0, $s4, CreatePseudo
	
GameProcess:
	la $t0, ($s2)
	la $s3, pseudoWord

	# Print guess promt and take input
	li $v0, 4
	la $a0, guessPromt
	syscall
	li $v0, 5
	syscall
	
	# Check user input and call GuessWord or GuessChar function
	# Save $t0
	subu $sp, $sp, 4
	sw $t0, ($sp)
	# beq $v0, 0, GuessWord
	# beq $v0, 1, GuessChar
	lw $t0, ($s0)
	addu $sp, $sp, 4

	# Check answer
	# Guess char 0: wrong, 1: correct
	# Guess word 2: lose, 3: win
CheckAnswer:
	beq $v0, 2, LoseScreen
	beq $v0, 3, WinScreen
	
	
WinScreen:
	# Print win message
	li $v0, 4
	la $a0, winMsg
	syscall
	# Print score
	li $v0, 4
	la $a0, scoreMsg
	syscall
	li $v0, 1
	la $a0, ($s1)
	syscall
	# Print win promt
	li $v0, 4
	la $a0, afterWinPromt
	syscall
	# Get input
	li $v0, 5
	syscall
	# Check input
	beq $v0, 1, 
	
LoseScreen:
	# Save player score to file
	move $a0, $s0
	move $a1, $s1
	jal WriteFile
	# Print lose message
	li $v0, 4
	la $a0, loseMsg
	syscall
	# Print score
	li $v0, 4
	la $a0, scoreMsg
	syscall
	li $v0, 1
	la $a0, ($s1)
	syscall
	# Print lose promt
	li $v0, 4
	la $a0, afterLosePromt
	syscall
	li $v0, 5
	syscall

SaveScore:
	

ExitGame:
