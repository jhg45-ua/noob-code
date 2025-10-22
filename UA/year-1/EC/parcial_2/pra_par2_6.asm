.data
	matriz_floats: .float	0.3, 2.3, 2.3,
			                0.1, 0.4, 0.3,
			                0.4, 0.1, 0.3
	N_filas: .byte	3
	mensaje1: .asciiz "\n--- PRIMER ELEMENTO DE CADA FILA ---\n"
	mensaje2: .asciiz "\n--- INDICES DE CADA CELDA ---\n"
	mensaje3: .asciiz "\n--- SUMA DE CADA FILA ---\n"
.text

	# --- IMPRIMIR PRIMER ELEMENTO DE CADA FILA ---
	li $v0, 4
	la $a0, mensaje1
	syscall

	lb $t0, N_filas
	sll $t0, $t0, 2		# N * 4 = tamaño de la fila por 4 bytes (float)
	li $t1, 1	# fila actual
	lb $t2, N_filas	# cantidad de filas
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

		# --- IMPRIMIR INDICES DE CADA CELDA ---
		li $v0, 4
		la $a0, mensaje2
		syscall

		lb $t0, N_filas	# $t0 = size
		li $t1,	0	# $t1 guarda el índice de fila
		la $t3, matriz_floats
	loop_row:
		beq $t1, $t0, end_loop_row
		li $t2, 0	# $t2 guarda el índice de columna
	loop_column:
		beq $t2, $t0, end_loop_column
		# Imprime el índice de fila
		li $v0, 1
		move $a0, $t1
		syscall
		# Imprime coma
		li $v0, 11
		li $a0, ','
		syscall
		# Imprime el índice de columna
		li $v0, 1
		move $a0, $t2
		syscall
		# Imprime salto de línea
		li $v0, 11
		li $a0, '\n'
		syscall
		add $t3, $t3, 4		# pasa al siguiente elemento
		addi $t2, $t2, 1
		j loop_column
	end_loop_column:
		addi $t1, $t1, 1
		j loop_row 
	end_loop_row:	

		# --- IMPRIMIR SUMA DE LOS ELEMENTOS DE CADA FILA ---
		li $v0, 4
		la $a0, mensaje3
		syscall

		lb $t0, N_filas	# $t0 = size
		li $t1,	0	# $t1 = i
		li $t2, 0	# $t2 = j
		la $t3, matriz_floats
		sub.s $f1, $f1, $f1	# Suma de la fila, pone $f1 en 0
	ini_matrix:
		beq $t1, $t0, fin_matrix
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
		sub.s $f1, $f1, $f1
		li $t2, 0
		addi $t1, $t1, 1
	no_cambio_fila:
		addi $t3, $t3, 4
		j ini_matrix
	fin_matrix:
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