# calculo de la media de una suma de un vector de enteros. (resutado real)
.data
	vector: 	.word 12, 32, 12, 35
	N:		.word 4	
.text
	la $a0, vector	# direccion de comienzo del vector
	lw $a1, N	# cantidad de elementos
	jal sumar	# deja en $v0, la suma de los elementos.
	
	mtc1 $v0, $f1	# copia en $f1 el $v0	(registros cpu => float)
	l.s $f2, N	# guardo en $f2 el valor que hay almacenado en N
	
	cvt.s.w $f1, $f1	# $f1 <= ieee($f1)
	cvt.s.w $f2, $f2	# $f2 <= ieee($f2)
	# antes de realizar la operacion debo asegurarme que los numeros estan en coma flotante.
	div.s $f12, $f1, $f2	# porque somos azules? porque estan en C2.
	
	li $v0, 2
	syscall
	# en $f12 esta la media.
	la $a0, vector
	lw $a1, N
	mfc1 $a2, $f12	# ahora el dato que esta en ieee => cpu		
	jal mayores_media
	move $s0, $v0 # me guardo la cantidad de elementos en $s0
	
	li $v0, 11
	li $a0, '\n'
	syscall
	
	move $a0, $s0 # imprimo el numero de valores
	li $v0, 1
	syscall
	
fin:
	li $v0, 10
	syscall
	
# en $a0 => direccion de comienzo del vector (de enteros)
# en $a1 => cantidad de elementos en el vector (entero)
# en $a2 => media de los elementos (obviamente real, como la vida misma)
# en $v0 => la cantidad de valores que superan la media
mayores_media:
	mtc1 $a2, $f1		# la media de los elementos del vector (el umbral)
	li $t0, 1 		# iteracion
	li $t1, 0 		# cantidad de elementos que superan
bucle_mayores_media:
	bgt $t0, $a1, fin_bucle_mayores_media  # itearcion > elementos vector (me piro vampiro)
	#############proceso el elemento########################
	l.s $f2, ($a0)
	cvt.s.w $f2, $f2
	c.le.s $f2, $f1 # elemento <= media
	bc1t seguir
es_mayor_que_media:
	addi $t1, $t1, 1
	########################################################
seguir:
	addi $a0, $a0, 4	# uso el $a0, para recorrer el vector, voy de 4 en 4.
	addi $t0, $t0, 1
	j bucle_mayores_media
fin_bucle_mayores_media:
	move $v0, $t1
	jr $ra


# guarda la suma de los elementos del vector
# hazte una funcion que recorra el vector y los sume broh
sumar:
	li $v0, 91
	jr $ra
	
