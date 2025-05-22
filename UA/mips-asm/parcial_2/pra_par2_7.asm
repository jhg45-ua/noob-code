.data 
	A:	.space 12
	B:	.space 12
	S:	.space 12

	AF:	.space 12
	BF:	.space 12
	SF:	.space 12
	
	N:	.byte 3
.text
	# lee A
	li $t0, 1 	# iteracion
	lb $t1, N	# cantidad
	la $t2, A	# elemento entero
	la $t3, AF	# elemento real
lee_A:
	bgt $t0, $t1, fin_lee_A
	
	# entero !!
	li $v0, 5
	syscall
	sw $v0, ($t2)
	
	# real !!
	li $v0, 6
	syscall
	s.s $f0, ($t3)
	
	addi $t2, $t2, 4	# Siguiente elemento entero...
	addi $t3, $t3, 4	# Siguiente elemento real
	addi $t0, $t0, 1 	# Una iteracion mas...
	j lee_A
fin_lee_A:

	############################################################
	# lee B
	li $t0, 1 	# iteracion
	lb $t1, N	# cantidad
	la $t2, B	# elemento entero
	la $t3, BF	# elemento real
lee_B:
	bgt $t0, $t1, fin_lee_B
	
	# entero !!
	li $v0, 5
	syscall
	sw $v0, ($t2)
	
	# real !!
	li $v0, 6
	syscall
	s.s $f0, ($t3)
	
	addi $t2, $t2, 4	# Siguiente elemento entero...
	addi $t3, $t3, 4	# Siguiente elemento real
	addi $t0, $t0, 1 	# Una iteracion mas...
	j lee_B
fin_lee_B:

	
			
	