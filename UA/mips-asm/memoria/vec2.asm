.data 
    msg1: .asciiz "Matriz 3x3\n"
    # Define matriz NxN
    matrix: .word 1,  4,  7,
            	  2,  5,  8,
            	  3,  6,  9
           
    n: .byte 3
.text

    ###### Progama principal
    
    la $a0, msg1 # Dir msg1
    li $v0, 4
    syscall
    
    jal print_newline
    
    la $a0, matrix
    lb $a1, n

    jal print_matrix_words

    li $v0, 10
    syscall

    ###### Funciones/Procedimientos
    print_matrix_words:
        move $t2, $a0 # direccion de comienzo de la matrix
        li $t0, 0 # Contador filas
    loop_row_words:
        bge $t0, $a1, end_loop_row_words
        li $t1, 0 # Contador columnas
    loop_columns_words:
        bge $t1, $a1 end_loop_columns_words
        ###### imprime fila
        #li $v0, 1
        #move $a0, $t0
        #syscall
        
        #jal print_coma
        
        #### Imprime columna
        #li $v0, 1
        #move $a0, $t1
        #syscall

        #jal print_space

        ##### Imprime elemento
        lw $a0, ($t2)
        li $v0, 1
        syscall

        jal print_space
	#jal print_newline

        addi $t2, $t2, 4 # Siguente direccion de la matrix
        add $t1, $t1, 1 # Siguiente columna
        j loop_columns_words
    end_loop_columns_words:
        addi $t0, $t0, 1 # Siguente fila
        jal print_newline
        j loop_row_words
    end_loop_row_words:
        jr $ra
        
    
    print_coma:
        li $v0, 11
        li $a0, ','
        syscall
        jr $ra
    print_space:
        li $v0, 11
        li $a0, ' '
        syscall
        jr $ra
    print_newline:
        li $v0, 11
        li $a0, '\n'
        syscall
        jr $ra
