##############################
#      Práctica 3 - EC       #
##############################
.text 0x00400000

##############################
#     C2 - escribir codigo   #
##############################
# rol $t1, $t2, 10
# ror $t1, $t2, 10
# 'rol' y 'ror' realiza dos desplazamientos, guarda por partes y luego hace una OR para combinarlo

##############################
#   C3 - Descubrir palabra   #
##############################
#	li $t1, 1215261793 # Palabra a descubrir
#	srl $a0, $t1, 24 # Letra H
#	li $v0, 11
#	syscall
	
#	srl $a0, $t1, 16 # Letra O
#	li $v0, 11
#	syscall

#	srl $a0, $t1, 8 # Letra L
#	li $v0, 11
#	syscall

#	move $a0, $t1 # Letra A
#	li $v0, 11
#	syscall

#	li $v0, 10 # Salir
#	syscall

###################################################################
#   A1-C4-C6-C7-C8 - Multiplicacion por desplazamientos y sumas   #
###################################################################
	li $a0 '>'
	li $v0, 11
	syscall
	li $v0, 5
	syscall

	move $a0, $v0 # Pasamos el valor pedido como paramatro de la funcion
	jal ecuacion
	# Para pasar de horas a segundos
	# jal mul60 # Vamos a la funcion
	# move $a0, $v0 # Lo hacemos dos veces para pasar de horas a segundos
	# jal mul60 
	move $a0, $v0
	li $v0, 1
	syscall

	li $v0, 10
	syscall

	# Funcion de x4
	cuadruple: add $t0, $a0, $a0 # $t0 = $a0 + $a0 = 2x $a0
		add $a0, $t0, $t0 # $a0 = 2x $a0 + 2x $a0 = 4x $a0
		
		move $v0, $a0 # Return de la funcion
		jr $ra
	
	# Otra forma de hacer la funcion anterior
	cuadruple2: sll $v0, $a0, 2
		jr $ra
	
	# Multiplicar por 5
	mul5: sll $v0, $a0, 2
		add $v0, $v0, $a0 # $v0 = 4x $a0 + $a0 = 5x $a0
		jr $ra
	
	# Multiplicar por 10
	mul10: sll $v0, $a0, 3 # $v0 = 8x $a0
		add $a0, $a0, $a0 # $a0 =2x $a0
		add $v0, $v0, $a0 # $v0=8x $a0 + 2x $a0 = 10x $a0
		jr $ra
	
	# Multiplicar por 60
	mul60: sll $v0, $a0, 6 # $v0 = 64x $a0
		sll $a0, $a0, 2 # $a0 = 4x $a0
		sub $v0, $v0, $a0 # $v0 = 64x $a0 - 4x $a0 = 60x $a0 
		jr $ra
    
    # Resuelve la ecuacion: 5x^2+2x+3 |-> x = $a0
	ecuacion: mult $a0, $a0 # lo = $a0 x $a0 = $a0ˆ2
		mflo $t0 # Movemos lo del registro lo a $t0 = $a0ˆ2
		sll $t1, $t0, 2 # $t1 = 4x $a0ˆ2
		add $t1, $t0, $t1 # $t1 = 4x $a0ˆ2 + $a0ˆ2 = 5x $a0ˆ2
		
		add $t1, $t1, $a0 # $t1 = 5x $a0ˆ2 + $a0
		add $t1, $t1, $a0 # $t1 = 5x $a0ˆ2 + 2x $a0
		
		addi $v0, $t1, 3 # $v0 = 5x $a0ˆ2 + 2x $a0 + 3

		jr $ra
