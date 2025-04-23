#   ------- Examen Grupo 6 -------
# 2. Realiza un programa que analice los datos de la matriz dada y mediante la llamada a una función a la
# que le pasamos la dirección del vector, calcule el valor máximo y mínimo de los valores de la citada
# matriz. La funci�n devolverá los valores máximo y mínimo y posteriormente almacenaremos el valor
# mínimo en la dirección 0x10010100 y el valor máximo en la dirección 0x10010103. Para finalizar , el
# programa mostrará los datos.
.data
	matriz: .byte 	2,  5,  9,
			        110,14, 18,
			        21, 33, 5
			
	Texto_final1: .asciiz "El valor mínimo es "
	Texto_final2: .asciiz " y el valor máximo es "
	Eti: .byte 0

.text
    # Inicio del programa
	la $a0, matriz
	
	# Llamamos a la funcion
	jal Buscar_en_matriz
	
Buscar_en_matriz:
	# $t0 se usa para ir cargando los bytes desde la memoria
	# $t1 se usa para guardar los mínimos
	# $t2 se usa para guardar los máximos
	li $t0, 0
	li $t1, 0x7FFFFFFF	# Registro máximo para poder guardar un número menor
	li $t2, 0
	
	li $t4, 1		# Se usa como contador auxiliar de las columnas
	Buscamos_por_columna:
		lb $t0, 0($a0)		# Cargamos el primer byte
		
		jal Comprobar_min
		jal Comprobar_max
		
		lb $t0, 3($a0)
		
		jal Comprobar_min
		jal Comprobar_max
		
		lb $t0, 6($a0)
		
		jal Comprobar_min
		jal Comprobar_max
		
		addi $a0, $a0, 1
		addi $t4, $t4, 1
		
		blt $t4, 3, Buscamos_por_columna
		
	# Si estamos aqu� hemos recorrido las tres columnas de la matrix y la funci�n
	# est� lista para devolver los valores
	
	move $v0, $t1		# Almacenamos en $v0 el valor menor
	move $v1, $t2		# Almacenamos en $v0 el valor mayor
		
	j Salir

Comprobar_min:
	slt $t3, $t0, $t1		# $t3 = 1, si $t0 < $t1
	beq $t3, 1, cambiar_min
	
	jr $ra

cambiar_min:
	add $t1, $t0, $zero
	
	jr $ra
	
Comprobar_max:
	sgt $t3, $t0, $t2		# $t3 = 1, si $t0 > $t2
	beq $t3, 1, cambiar_max
	
	jr $ra
	
cambiar_max:
	add $t2, $t0, $zero
	
	jr $ra
	
Salir:
	sb $v0, 0x10010100
	sb $v1, 0x10010103
	
	move $s0, $v0
	move $s1, $v1
	
	la $a0, Texto_final1
	li $v0, 4
	syscall
	
	move $a0, $s0
	li $v0, 1
	syscall
	
	la $a0, Texto_final2
	li $v0, 4
	syscall
	
	move $a0, $s1
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall