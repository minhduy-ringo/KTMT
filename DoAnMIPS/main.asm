# Hang man game
.data
tMenu:		.asciiz "===================Menu===================\n"
tNewGame: 	.asciiz "1.New game\n"
tPlayAgain: 	.asciiz "2.Play again\n"
tScoreboard: 	.asciiz "3.Score board\n"
tExit: 		.asciiz "4.Exit\n"
tChoose: 	.asciiz "Choose:"
FirstWrong:	.asciiz "\n______\n|/   |\n|\n|\n|\n|\n|\n"
SecondWrong:	.asciiz "\n______\n|/   |\n|    O\n|\n|\n|\n|\n"
ThirdWrong:	.asciiz "\n______\n|/   |\n|    O\n|    |\n|\n|\n|\n"
FourthWrong:	.asciiz "\n______\n|/   |\n|    O\n|   /|\n|\n|\n|\n"
FifthWrong:	.asciiz "\n______\n|/   |\n|    O\n|   /|\\\n|\n|\n|\n"
SixthWrong:	.asciiz "\n______\n|/   |\n|    O\n|   /|\\\n|   /\n|\n|\n"
SeventhWrong:	.asciiz "\n______\n|/   |\n|    O\n|   /|\\\n|   / \\\n|\n|\n"

#
error:		.word
CheckWrong:	.word 7
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
	# test draw Hangman
	beq $v0,5,DrawHangMan
	j MenuLoop

#
DrawHangMan:
	lw $s0,CheckWrong

	beq $s0,1,Fwrong
	beq $s0,2,Swrong
	beq $s0,3,Twrong
	beq $s0,4,Fowrong
	beq $s0,5,Fiwrong
	beq $s0,6,Siwrong
	beq $s0,7,Sewrong
Fwrong:
	li $v0,4
	la $a0,FirstWrong
	syscall
	jal GoExit
Swrong:
	li $v0,4
	la $a0,SecondWrong
	syscall
	jal GoExit
Twrong:
	li $v0,4
	la $a0,ThirdWrong
	syscall
	jal GoExit
Fowrong:
	li $v0,4
	la $a0,FourthWrong
	syscall
	jal GoExit
Fiwrong:
	li $v0,4
	la $a0,FifthWrong
	syscall
	jal GoExit
Siwrong:
	li $v0,4
	la $a0,SixthWrong
	syscall
	jal GoExit
Sewrong:
	li $v0,4
	la $a0,SeventhWrong
	syscall
	jal GoExit
	
GoGame:
	#jal Game
	jal GoExit

GoExit:
	li $v0,10
	syscall
