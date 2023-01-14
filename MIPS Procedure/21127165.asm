.data
	array: .space 396
	inputNumberOfElements: .asciiz "Nhap so phan tu (1-99): "
	inputElementMsg: .asciiz "Nhap phan tu thu "
	sumOddMsg: .asciiz "Tong cac so le: "

	count: .word 0

	space: .asciiz " "
	endl: .asciiz "\n"
	colon: .asciiz ":"

.text

main:
	InputSize:
		li $v0, 4
		la $a0, inputNumberOfElements
		syscall
	
		li $v0, 5
		syscall
	
		move $t0, $v0
		blt $t0, 1, InputSize
		bgt $t0, 99, InputSize
		
	la $t1, array

#===========inputArray==============
	lw $s2, count
	LoopInput:
		#=======Input Message======
		li $v0, 4
		la $a0, inputElementMsg
		syscall
		
		addi $s3, $s2, 1
		li $v0, 1
		move $a0, $s3
		syscall
		
		li $v0, 4
		la $a0, colon
		syscall
		
		li $v0, 4
		la $a0, space
		syscall
		
		#========================
		
		#=======Input=========
		li $v0, 5
		syscall
		
		sw $v0, 0($t1)
		
		addi $t1, $t1, 4
		addi $s2, $s2, 1
		
		blt $s2, $t0, LoopInput

#============outputArray===============
	lw $s2, count
	la $t1, array
	LoopPrint:
		lw $s0, 0($t1)
		
		li $v0, 1
		move $a0, $s0
		syscall
		
		li $v0, 4
		la $a0, space
		syscall
		
		addi $t1, $t1, 4
		addi $s2, $s2, 1
		
		blt $s2, $t0, LoopPrint
	
	li $v0, 4
	la $a0, endl
	syscall
	
	#========Sum All Odd Elements========
	la $t1, array
	jal sumOddArray
	
	#=====Display=====
	li $v0, 4
	la $a0, sumOddMsg
	syscall
	
	li $v0,1
	move $a0, $s3
	syscall
	
	li $v0, 4
	la $a0, endl
	syscall
	#==============
	#==========End Program==========
	j Exit

#==Other procedures	
sumOddArray:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	lw $s2, count
	addi $s3, $zero, 0
	LoopSum:
		lw $t6, 0($t1)
		
		addi $s4, $zero, 0
		jal isOdd
		beq $s4, 0, Continue
		
		add $s3, $s3, $t6
		
		Continue:
			addi $s2, $s2, 1
			addi $t1, $t1, 4
		
		blt $s2, $t0, LoopSum
		
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	
	jr $ra
	
isOdd:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	and $s4, $t6, 1
	
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	
	jr $ra

Exit:
	li $v0, 10
	syscall
