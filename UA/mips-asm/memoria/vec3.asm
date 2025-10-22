.data
	str: .ascii "Estructuras de los"
	.asciiz "Computadores"
	str2: .asciiz "El número de caracteres de la cadena es: "
	str3: .asciiz "El número de caracteres u en la cadena es: "
.text
	la $s0, str
	add $s1, $zero, $zero # Iniciamos contador a 0
	add $s2, $zero, $zero # Contador de U
	li $t2, 'u' 
	loop:
		add $t0, $s0, $s1 # dirección del byte a examinar
		lb $t1, 0( $t0 )
		beq $t1, $zero, exit # salimos si carácter leído='\0'
		addi $s1, $s1, 1 # incrementamos el contador
		bne $t1, $t2, loop # Saltar cuando no es U
		addi $s2, $s2, 1
		j loop
		
	
	exit: 
	la $a0, str2
	li $v0, 4
	syscall
	move $a0, $s1
	li $v0, 1
	syscall
	la $a0, str3
	li $v0, 4
	syscall
	move $a0, $s2
	li $v0, 1
	syscall
	li $v0, 10
	syscall