# Hang man game
.data
tMenu:		.asciiz "===================Menu===================\n"
tNewGame: 	.asciiz "1.New game\n"
tPlayAgain: 	.asciiz "2.Play again\n"
tScoreboard: 	.asciiz "3.Score board\n"
tExit: 		.asciiz "4.Exit\n"
tChoose: 	.asciiz "Choose:"

#
error:		.word

.text

.globl main
main:
	# Display menu
	li $v0, 4
	la $a0, tMenu
	syscall
	li $v0, 4
	la $a0, tNewGame
	syscall
	li $v0, 4
	la $a0, tPlayAgain
	syscall
	li $v0, 4
	la $a0, tScoreboard 
	syscall
	li $v0, 4
	la $a0, tExit
	syscall

	# Check user choosed input
MenuLoop:
	# Choose game option
	li $v0, 4
	la $a0, tChoose
	syscall
	li $v0, 5
	syscall

	beq $v0,1,GoGame
	# beq $v0,2,GoAgain
	# beq $v0,3,GoScoreboard
	beq $v0,4,GoExit
	j MenuLoop

#
GoGame:
	jal Game

GoExit:
	li $v0,10
	syscall