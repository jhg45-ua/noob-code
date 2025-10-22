.text
	li $s1, 1
bucle:
	bgt $s1, 10, fin_bucle # si $s1 > 10 entonces salto a fin_bucle
	li $v0, 1
	move $a0, $s1
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall 
	addi $s1, $s1, 1
	j bucle	
fin_bucle:
	li $v0, 10
	syscall