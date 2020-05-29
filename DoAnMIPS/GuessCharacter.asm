.data
	tNhapkytu:	.asciiz "Nhap ky tu: "
	mess:		.asciiz "hello"
	#
	wordlength:	.word 5
.text
.globl main
main:
	#xuat thong bao
	li 	$v0,4
	la 	$a0,tNhapkytu
	syscall
	#Nhap ky tu
	li 	$v0,12
	syscall
	move 	$a0,$v0
	
	#load
	#$a0: guessinput
	#$a1: word
	#$a2: wordlength

	la 	$a1,mess
	lw	$a2,wordlength
	li	$t1,0		#khoi tao bien dem
	jal 	CheckCharacter

	move	$a0,$v0

	li	$v0,1
	syscall

	jal	GoExit	
CheckCharacter:
	addi	$sp,$sp,0
	sw	$ra,($sp)
	
	lb	$s0,0($a1)
	addi 	$t1,$t1,1	#tang bien dem
	addi	$a1,$a1,1	#tang dia chi ky tu ke tiep
	
	beq	$s0,$a0,CheckCharacter.returnPos#kiem tra ky tu nhap
	
	slt	$t0,$t1,$a2
	beq	$t0,1,CheckCharacter	#kiem tra dieu kien lap
	bne	$v0,0,CheckCharacter.returnFalse

	addi 	$sp,$sp,0
	lw	$ra,($sp)
CheckCharacter.returnFalse:
	addi	$v0,$0,-1
	jr $ra
CheckCharacter.returnPos:
	move	$v0,$t1
	jr	$ra
GoExit:
	li $v0,10
	syscall
