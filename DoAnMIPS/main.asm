# Hang man game
.data
welcomeMsg:	.asciiz "Welcome to the hang man game\n"
namePromt:	.asciiz "Please type in your player name: "
menuMsg:	.asciiz "===================Menu===================\n"
newGameOpt: 	.asciiz "1.Play\n"
scoreboardOpt: 	.asciiz "2.Score board\n"
exitOpt: 	.asciiz "3.Exit\n"
exitMsg:	.asciiz "Thanks you for playing!!\n"
chooseMsg: 	.asciiz "Choose: "

breakBar:	.asciiz "==========================================\n"

#
playerName:	.space 32

.text

.globl main
main:
	li 	$v0, 4
	la 	$a0, welcomeMsg
	syscall
	# Player name promt
	li 	$v0, 4
	la 	$a0, namePromt
	syscall
	li 	$v0, 8
	la 	$a0, playerName
	la 	$a1, 32
	syscall
	li 	$v0, 11
	li 	$a0, 10
	syscall
Menu:
	# Display menu
	li 	$v0, 4
	la 	$a0, menuMsg
	syscall
	li 	$v0, 4
	la 	$a0, newGameOpt
	syscall
	li 	$v0, 4
	la 	$a0, scoreboardOpt
	syscall
	li 	$v0, 4
	la 	$a0, exitOpt
	syscall
	li 	$v0, 4
	la 	$a0, breakBar
	syscall

	# Check user choosed input
MenuLoop:
	# Choose game option
	li 	$v0, 4
	la 	$a0, chooseMsg
	syscall
	li 	$v0, 5
	syscall

	beq 	$v0,1,GoGame
	beq 	$v0,2,GoScoreBoard
	beq 	$v0,3,GoExit
	j 	MenuLoop
#
GoGame:
	# $a0 = player name
	la 	$a0, playerName
	jal 	Game
	j	Menu

GoScoreBoard:
	#jal 	ScoreBoard
	j	Menu

GoExit:
	li 	$v0, 4
	la 	$a0, exitMsg
	syscall
	li 	$v0,10
	syscall

.ktext 0x80000180
	mfc0 $k0,$14   # Coprocessor 0 register $14 has address of trapping instruction
   	addi $k0,$k0,4 # Add 4 to point to next instruction
   	mtc0 $k0,$14   # Store new address back into $14
   	eret           # Error return; set PC to value in $14
