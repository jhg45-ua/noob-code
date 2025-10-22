# mostrar la suma de dos valores reales almacenados en la memoria nazi.
.data
	eldos: 		.word 0x40000000 # esto es ieee
	eldos_medio:	.float 2.5 # .word 0x40200000
	eldos_easy: 	.float 2 # esto es ieee
	eldosentero: 	.word 2 # esto es c2 0x00000002

.text
	# que pasa si quiero sumar el 2 y el 2.5
	# add $0, $1, $2 => suma de la ALU son en C2
	
	# las instrucciones para cargar los datos de la memoria al coprocesador no son loas mismas
	# que las de lw y sw
	
	l.s $f1, eldos		# mueve un dato de la memoria (simple precision) al coprocesador matematico.
	
	la $a0, eldos_medio 	# cargo la direccion de la etiqueta en $a0 = 0x
	l.s $f2, 0($a0)		# cargo el dato con formato (registro base + desplazamiento) para acceder a memoria.
				# $f2 = M[$a0 + 0] = M[$a0]
				
	# no existe suma dato inmediato con numeros reales, tenemos que tener en los registros $f
	add.s $f1, $f1, $f2 	# ya tengo la suma en $f1.
	
	mov.s $f12, $f1		# transferencia de registro a registro de numeros reales.

	li $v0, 2		# imprimir float
	syscall

fin:
	li $v0, 10
	syscall
	
