.data
	X:	.float -1, -2,  3, -4 #.float 1.0, -2.0, 3.0, -4.0 # ieee3 sp 32 bits, por cada valor
	W:	.float -2,  2, -3,  1 #.float 5.0, -6.0, 7.0, -8.0
	b:	.float 0.2
	a:	.float 0.3
.text
	la $a0, X
	la $a1, W
	l.s $f12, b	# copia un dato de la memoria a un registro $f
	jal perceptron  # $f0 <=  resultado

	mov.s $f12, $f0
	li $v0, 2
	syscall
	
	li $a0, '\n'
	li $v0, 11
	syscall		# cout << endl;
	
	mov.s $f12, $f0
	jal LReLU
	mov.s $f12, $f0
	li $v0, 2
	syscall

	li $a0, '\n'
	li $v0, 11
	syscall		# cout << endl;

fin:
	li $v0, 10
	syscall
	
# $a0 <= la direccion de comienzo de X
# $a1 <= la direccion de comienzo de Y 
# $f12 <= el valor de b	
# $f0 resultado de la funcion :) jeje
perceptron:
	li $t0, 1
	sub.s $f0, $f0, $f0	# $f0 = 0 (suma escalar acumulada)
bucle_perceptron:
	bgt $t0, 4, fin_bucle_perceptron
	l.s $f1, ($a0)	# $a0 direccion del elemento actual 
	l.s $f2, ($a1)  # $a1 direccion del elemento siguiente
	mul.s $f1, $f1, $f2
	add.s $f0, $f0, $f1
	addi $t0, $t0, 1
	addi $a0, $a0, 4 # siguiente elemento en X
	addi $a1, $a1, 4 # siguiente elemento en W
	j bucle_perceptron
fin_bucle_perceptron:
	add.s $f0, $f0, $f12
	jr $ra

# Crea otra función llamada ‘LReLU’ que reciba un valor x en coma flotante como parámetro y devuelva x*a si es
# menor o igual que 0.0 ó x en otro caso. Donde a es el valor entre 0.0 y 0.5 que elijas.	
# $f12 <= valor resibido (x)
# $f0 => valor devuelto
LReLU:
	sub.s $f0, $f0, $f0  # $f0 = 0
	c.le.s $f12, $f0 # el resultado de la comparacion se guarda en un registro interno (flag)
	bc1f fin_LReLU
	l.s $f11, a
	mul.s $f12, $f12, $f11 # x = x * a
fin_LReLU:
	mov.s $f0, $f12 # return x
	jr $ra


	
# * Realiza un funcion que reciba un vector de reales, cantidad de elementos que tiene el vector
# y un umbral maximo, de forma que la funcion devuelve la suma de los elementos del vector
# sin que supere el umbral maximo.
