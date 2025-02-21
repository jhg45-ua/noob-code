.text
	# Practica 4. Ejercicio 1.
	# ¿Con qué instrucciones traducirá el ensamblador 
	# las pseudoinstrucciones rol y ror?. Escribe un 
	# código sencillo de prueba de ambos operadores y 
	# ensámblalos para comprobarlo.

	########################################################
	# Test 1.
	# ¿Que hay en el registro $t1, despues de realizar la rotacion?
	# rol => rotacion a la izquierda.
	li $t1, 0xABCD7654
	rol $t1, $t1, 4
	li $v0, 34
	move $a0, $t1
	syscall	
	
	# Respuesta: # $t1 = BCD7 654A
	
	#######################################################
	# Test A.
	li $t1, 0xABCD7654
	ror $t1, $t1, 0xc
	li $v0, 34
	move $a0, $t1
	syscall
		
	# ¿Que imprime por pantalla?
	# 0x654A BCD7
	
	#######################################################
	# Test B.
	li $t1, 0xABCD6666
	sll $t2, $t1, 0x10 	# $t2 = 0x66660000
	srl $t3, $t1, 16	# $t3 = 0x0000ABCD
	or $t4, $t2, $t3
	# ¿Que hay en el regitro $t4 despues de ejecutar este codigo? 
	# $t4 = 0x6666ABCD
	
	#######################################################
	# Test 2.
	# Dado el siguiente codigo, a que instruccion rol corresponderia
	#
	li $9, 0xABCD7654
	srl $1, $9, 0x1c 	# $1 = 0x0000000A	
	sll $9, $9, 0x04	# $9 = 0xBCD76540
	or $9, $9, $1		# $9 = 0xBCD7654A

	# Respuesta: rol $9, $9, 4
	
	######################################################
	# Test 3.
	# Que numero imprime por pantalla el siguiente codigo.
	li $t1, 0xFFFFFFF8 	# 1111111...1000 => -8
	sra $t1, $t1, 2 	# 1111111...1110 => -2 
	li $v0, 1
	addu $a0, $zero, $t1	
	syscall	
	
	# Respuesta: 
	# print entero => -2
	# si el servicio fuera el 34 => 0xFFFF FFFE
	
	##################################################
	# Test 4.	
	# Que numero imprime por pantalla el siguiente codigo.
	####################################################
	li $t1, 0x10 			# $t1 = 16
	sra $t1, $t1, 2 		# $t1 = 010000 => 001000 => 000100 
	li $v0, 1
	addu $a0, $zero, $t1		
	syscall	
	li $v0, 10
	syscall
	# partimos del 16
	# 1 0000
	# Respuesta: 4
	
	###################################################
	# Test C
	# Que numero imprime por pantalla?.
	###################################################
	li $t1, 0x1F		# 0x011111 => 0x01111 => 0x111
	sra $t1, $t1, 2 
	li $v0, 1
	addu $a0, $zero, $t1		
	syscall	
	li $v0, 10
	syscall

	# Respuesta: 7
	
	###########################################
	# Test 5.
	# ¿Cual es el contenido del registros
	#	rs = 0
	#	rt = 11 ($t3)
	#	rd = 9 ($t1)
	# 	shmt = 0101 => aqui almacena el desplazamiento!!
	# para la instruccion siguiente si $t0 es $8?

	sll $t1, $t3, 5 # sll rd, rt, shmt
	
	# Respuesta
	# 	Tipo R
	#
	#	cop	rs	rt	rd	shmt	func
	#	000000 00000  01011  01001    00101   000000

	# 	0x000b4940
	#
	#	0000 0000 0000 1011 0100 1001 0100 0000
	
	#############################################################
	# Test 6.
	# Dada la siguiente instruccion
	# add $t0, $t1, $t2 		
	#	que se almacenaria en el campo
	#	rs, rt y rd a la hora de codificar la instruccion
	# sabiendo que $t0 es el registro 8 del banco de registros.?
	#
	#
	# Respuesta
	# 	add rd, rs, rt
	#	tipo R = cop Rs Rt Rd shmt func
	#	rs = 01001
	#	rt = 01010
	#	rd = 01000
	#
	#############################################################
	
	#########################################
	# Test d.
	# Sabiendo que el campo funct de la instruccion add es 32
	# Indica cual es la codificacion en hexadecimal de la instruccion
	# add $t1, $t2, $t3
	#
	#	cop	rs	rt	rd	shmt	funct
	#	000000  01010	01011	01001	00000	100000
	#	
	#	0000.00  01.010	0.1011.	0100.1	000.00	10.0000
	#	0 1 4 B 4 8 2 0
	

	############################################################
	# Test 7.
	# Dada la siguiente instruccion ($t0 equiv. $8)
	# addi $t2, $t6, 10
	# elige:
	# 	a)
	#		rs = 01110
	#		rd = 01010
	#		datoI = 0x000A
	#	b)
	#		
	#		rs = 01110
	#		rt = 01010
	#		datoI = 0x000A
	###########################################################
	# Respuesta TIPO I: cop Rs Rt desp
	# b)
	
	
	#########################################
	# Test E.
	# Dada la siguiente instruccion ($t0 equiv. $8)
	# addi $t2, $t6, 10 # $t2 = $t6 + 10
	# y sabiendo que el codigo de operacio de la instruccion adi es 0x08
	# Indica cual es la codificacion en hexadecimal de la siguiente instruccion:
	###########################################
	
	# Respuesta:
	
	# cop		rs		rt		dato
	# 0010.00	01.110		0.1010.		0000 0000 0000 1010
	#
	#	2 1 C A 0 0 0 A
	
	
	########################################################
	# Test 8.
	# Dado el siguiente codigo, ¿Que instrucciones de desplazamiento tendriamos 
	# que añadir para que se multplique por 10?
	
mult10: 
	sll $v0, $a0, 2 #Función multiplica entero por 4 

#	a)
	add $v0, $v0, $v0 # x4 + x4 = x8
	add $v0, $v0, $a0
	add $v0, $v0, $a0
	jr $ra	
	
	################################################
	# Test 9.
	# Multiplicar $a0 x 18 y dejar el resultado en $v0
	#
	sll $v0, $a0, 4		#  x 2^4
	sll $v1, $a0, 1		#  x 2
	add $v0, $v0, $v1

	###############################################3
	# Test 10
	# Que almacena finalmente el registro $v0
	
	sll $v0, $a0, 2
	sll $v1, $a0, 3
	add $v0, $v0, $v1
	add $v0, $v0, $a0
	
	# Respuesta
	# sll $v0, $a0, 2	=> $v0 = 4 x $a0
	# sll $v1, $a0, 3	=> $v1 = 8 x $a0
	# add $v0, $v0, $v1	=> $v0 = 12 x $a0
	# add $v0, $v0, $a0	=> $v0 = 13 x $a0

	#################################################
	# Test	11
	# Dado el siguiente codigo:
	li $a0, 12
	li $a1, 14
	jal funcion	# en $ra = siguiente instruccion
			# en $pc = direccion de funcion
	move $a0, $v0 # para conservar el valor devuelto
	# y ademas aprovecho para pasar el argumento a syscall.
	
	li $v0, 4
	syscall
	li $v0, 10
	syscall
funcion:
	add $v0, $a0, $a1
	jr $ra # $pc = $ra
	
	# que imprime por pantalla?
	
	# que se guarda en el registro $ra?
	#  En $ra se guarda la direccion de la siguiente instruccion,
	# para poder volver a esa insturccion modificando jump register
	# $ra
	
	################################################
	# Test 12
	# Hay un problema en este programa, donde esta?
	
	li $a0, 12
	li $a1, 14
	jal funcion
	li $v0, 4		
	move $a0, $v0
	syscall
	
	# Respuesta: Estoy chafando el valor devuelto con 
	# el numero de servicio.
	
	# Todos los loads que no superan los 16 bits
	# se traducen a addiu (no extienden signo)
	li $t3, 0x40
	#equivalente
	addiu $t3, $zero, 0x40
	
	li $t4, 0x80
	#equivalente
	addiu $t4, $zero, 0x30

	# Si un load supera los 16 bits usa upper-inmediate
	# y ori
	li $t1, 0x89ABCDEF
	# equivalente
	lui $t1, 0x89AB
	ori $t1, $t1, 0xCDEF


	addi $t1, $zero, 0x80   # resultado positivo
	subi $t1, $zero, 0x80 	# resultado negativo
				# $t1 = 0xFFFF FF80

	# addi vs addiu
	# ambas operaciones se hacen en c2, independientemente
	# de su (u), la unica diferencia es el overflow.
					
	addiu $t1, $zero, 0x80000000
	# addi $t1, $t1, 0x80000000 # Arithmetic overflow
	addiu $t1, $t1, 0x80000000 # $t1 = 0
	
	
	# desplazamientos y rotaciones nazis.
	li $t1, 0xabcd0707
	rol $t1, $t1, 4
	
	
	
	li $v0, 10
	syscall
