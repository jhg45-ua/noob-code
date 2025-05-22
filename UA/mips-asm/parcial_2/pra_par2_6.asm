.data
	matriz_floats: .float	0.3, 2.3, 2.3,
			                0.1, 0.4, 0.3,
			                0.4, 0.1, 0.3
	N: .byte	3
.text
	# Imprimid el primer elemento de cada fila.
	lb $t0, N
	sll $t0, $t0, 2		# N * 4 = tam fila en bytes
	
	li $t1, 1	# fila actual
	lb $t2, N	# cantidad de filas
	la $t3, matriz_floats # direccion del elemento
loop_print:
	bgt $t1, $t2, end_loop_print
	l.s $f12, ($t3)
	li $v0, 2
	syscall	# cout << $f12 (real);
	li $v0, 11
	li $a0, '\n'
	syscall	# cout << endl;
	add $t3, $t3, $t0	# actual + tam_fial
	addi $t1, $t1, 1 	# siguiente iteracion
	j loop_print
end_loop_print:
	# Mostrad los elementos de cada fila:
	# $t0 = size
	lb $t0, N	# $t0 = size
	li $t1,	0	# $t1 = i
	la $t3, matriz_floats
loop_row:
	beq $t1, $t0, end_loop_row
 	li $t2, 0
 	# estoy empezamndo una fila nueva
loop_column:
	beq $t2, $t0, end_loop_column
	# esta en una celda
	#####################################
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 11
	li $a0, ','
	syscall
	li $v0, 1
	move $a0, $t2
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	#####################################
	add $t3, $t3, 4		# pasa al siguiente
	addi $t2, $t2, 1
	j loop_column
end_loop_column:

# estoy cambiando de fila
  	addi $t1, $t1, 1
   	j loop_row 
end_loop_row:	
	lb $t0, N	# $t0 = size
	li $t1,	0	# $t1 = i
	li $t2, 0	# $t2 = j
	la $t3, matriz_floats
	sub.s $f1, $f1, $f1	# suma de la puta fila. $f1 = 0
ini_matrix:
	beq $t1, $t0, fin_matrix
	# procesar el elementode $t3
	l.s $f2, ($t3)
	add.s $f1, $f1, $f2
	addi $t2, $t2, 1
	blt $t2, $t0, no_cambio_fila
cambio_fila:
	li $v0, 2
	mov.s $f12, $f1
	syscall

	li $v0, 11
	li $a0, '\n'
	syscall

	# cabmio de linea
	sub.s $f1, $f1, $f1
	li $t2, 0
	addi $t1, $t1, 1
no_cambio_fila:
	addi $t3, $t3, 4
	j ini_matrix
fin_matrix:
	# Mostrad la suma de los elementos de cada
	li $v0, 10
	syscall
	
#	int i, j;
#	int n;
#	i = 0;
#	j = 0;
#	while(i < n){
#		cout << m[i][j];
#		j++;
#		if(j == n){
#			j = 0;
#			i++;
#		}
#	}





