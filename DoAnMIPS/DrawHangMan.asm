.data
# Gallow visual
gBarTop: 	.asciiz "--------------\n"
gBarTop2: 	.asciiz "|/           |\n"
gStand: 	.asciiz "|\n|\n|\n|\n|\n"

# Hangman visual
FirstWrong:	.asciiz "\n______\n|/   |\n|\n|\n|\n|\n|\n"
SecondWrong:.asciiz "\n______\n|/   |\n|    O\n|\n|\n|\n|\n"
ThirdWrong:	.asciiz "\n______\n|/   |\n|    O\n|    |\n|\n|\n|\n"
FourthWrong:.asciiz "\n______\n|/   |\n|    O\n|   /|\n|\n|\n|\n"
FifthWrong:	.asciiz "\n______\n|/   |\n|    O\n|   /|\\\n|\n|\n|\n"
SixthWrong:	.asciiz "\n______\n|/   |\n|    O\n|   /|\\\n|   /\n|\n|\n"
SeventhWrong:.asciiz "\n______\n|/   |\n|    O\n|   /|\\\n|   / \\\n|\n|\n"

.text

.globl DrawHangMan

# How to call
# $a0 = number of error
# jal WriteFile

DrawHangMan:
	subu 	$sp, $sp, 4
	sw	$ra, ($sp)
	
	# Draw hang man base on number of error input
	# $a0 = number of error
	move 	$t0, $a0
	beq 	$t0,1,Fwrong
	beq 	$t0,2,Swrong
	beq 	$t0,3,Twrong
	beq 	$t0,4,Fowrong
	beq 	$t0,5,Fiwrong
	beq 	$t0,6,Siwrong
	beq 	$t0,7,Sewrong
Fwrong:
	li 	$v0,4
	la 	$a0,FirstWrong
	syscall
	jal 	GoExit
Swrong:
	li 	$v0,4
	la 	$a0,SecondWrong
	syscall
	jal 	GoExit
Twrong:
	li 	$v0,4
	la 	$a0,ThirdWrong
	syscall
	jal 	GoExit
Fowrong:
	li 	$v0,4
	la 	$a0,FourthWrong
	syscall
	jal 	GoExit
Fiwrong:
	li 	$v0,4
	la 	$a0,FifthWrong
	syscall
	jal 	GoExit
Siwrong:
	li 	$v0,4
	la 	$a0,SixthWrong
	syscall
	jal 	GoExit
Sewrong:
	li 	$v0,4
	la 	$a0,SeventhWrong
	syscall
	jal 	GoExit

GoExit:
	lw 	$ra, ($sp)
	addu 	$sp, $sp, 4
	jr $ra
