# Hang man game
.data
welcomeMsg:	.asciiz "Welcome to the hang man game\n\n"
namePromt:	.asciiz "Please type in your player name: "
menuMsg:	.asciiz "===================Menu===================\n"
newGameMsg: 	.asciiz "1.Play\n"
scoreboardMsg: 	.asciiz "2.Score board\n"
exitMsg: 	.asciiz "3.Exit\n"
chooseMsg: 	.asciiz "Choose: "

#
playerName:	.space 32

.text

.globl main
main:
	li $v0, 4
	la $a0, welcomeMsg
	syscall
	# Player name promt
	li $v0, 4
	la $a0, namePromt
	syscall
	li $v0, 8
	la $a0, playerName
	la $a1, 32
	syscall

	# Display menu
	li $v0, 4
	la $a0, menuMsg
	syscall
	li $v0, 4
	la $a0, newGameMsg
	syscall
	li $v0, 4
	la $a0, scoreboardMsg 
	syscall
	li $v0, 4
	la $a0, exitMsg
	syscall

	# Check user choosed input
MenuLoop:
	# Choose game option
	li $v0, 4
	la $a0, chooseMsg
	syscall
	li $v0, 5
	syscall

	beq $v0,1,GoGame
	beq $v0,3,GoScoreBoard
	beq $v0,4,GoExit
	j MenuLoop

#
GoGame:
	# $a0 = player name
	la $a0, playerName
	jal Game

GoScoreBoard:

GoExit:
	li $v0,10
	syscall
