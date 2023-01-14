.data
	nhapA: .asciiz "Nhap A: "
	nhapB: .asciiz "Nhap B: "
	Cong: .asciiz "A + B = "
	Tru: .asciiz "A - B = "
	Nhan: .asciiz "A * B = "
	Chia: .asciiz "A / B = "
	Mod: .asciiz "A % B = "
	LoiChia0: .asciiz "Loi chia cho 0!"
.text
main:

#====NHAP A=====
li $v0, 4
la $a0, nhapA
syscall

li $v0, 5
syscall
move $s0, $v0

#====NHAP B=====
li $v0, 4
la $a0, nhapB
syscall

li $v0, 5
syscall
move $s1, $v0

	#=====Cong=====
	li $v0, 4
	la $a0, Cong
	syscall
	
	add $s2, $s0, $s1
	li $v0,1
	move $a0,$s2
	syscall
	
	#**endl**
	li $v0, 11
	li $a0, '\n'
	syscall

	#====Tru====
	li $v0, 4
	la $a0, Tru
	syscall
	
	sub $s3, $s0, $s1
	li $v0, 1
	move $a0, $s3
	syscall
	
	#**endl**
	li $v0, 11
	li $a0, '\n'
	syscall
	
	#====Nhan====
	li $v0, 4
	la $a0, Nhan
	syscall
	
	mul $s4, $s0, $s1
	li $v0, 1
	move $a0, $s4
	syscall

	#**endl**
	li $v0, 11
	li $a0, '\n'
	syscall
	
	#============
	beqz $s1, ChiaCho0
	
	div $s0, $s1

	#====Chia====
	li $v0, 4
	la $a0, Chia
	syscall
	
	mflo $s5
	li $v0, 1
	move $a0, $s5
	syscall
	
	#**endl**
	li $v0, 11
	li $a0, '\n'
	syscall
	
	#====Mod====
	li $v0, 4
	la $a0, Mod
	syscall
	
	mfhi $s6
	li $v0, 1
	move $a0, $s6
	syscall
	
	#**endl**
	li $v0, 11
	li $a0, '\n'
	syscall
	
	li $v0, 10
	syscall

ChiaCho0:
	li, $v0, 4
	la $a0, LoiChia0
	syscall
	li $v0, 10
	syscall
