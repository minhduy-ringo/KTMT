.data
# Gallow visual
gBarTop: 	.asciiz "--------------\n"
gBarTop2: 	.asciiz "|/           |\n"
gStand: 	.asciiz "|\n|\n|\n|\n|\n"

# Hangman visual
mHead:   	.asciiz "|            O\n"
mBody:   	.asciiz "|            |\n"
mLeftArm: 	.asciiz "|           /| \n"
mRightArm:	.asciiz "|           /|\\ \n"
mLeftLeg: 	.asciiz "|           /\n"
mRightLeg:	.asciiz "|           / \\ \n"
mLeftOverStand: .asciiz "|\n|\n"

.text

# Draw hang man
.globl DrawHangMan
DrawHangMan:
	li $v0, 4
	la $a0, gBarTop
	syscall
	li $v0, 4
	la $a0, gBarTop2
	syscall
	li $v0, 4
	la $a0, mHead
	syscall
	li $v0, 4
	la $a0, mRightArm
	syscall
	li $v0, 4
	la $a0, mRightLeg
	syscall
	li $v0, 4
	la $a0, mLeftOverStand
	syscall
	jr $ra
