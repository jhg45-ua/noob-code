.data
    vector: .space 10

.text
    la $s0, vector

    li $t0, 0
    li $t1, 1
    init:
        bge $t0, 10, salir_bucle
        sb $t1, vector($t0)
        addi $t1, $t1, 1
        addi $t0, $t0, 1
        j init
    salir_bucle:
        li $v0, 10
        syscall


    # $a0 => direccion de inicio del vector
    # $a1 => cantidad de elementos del vector
    # $a2 => el valor para inicializar vector
    # $a3 => caractere separador
    ini_vector:
        li $t0, 0   # Cantidad de iteraciones
    bucle_ini_vector:
        bgt $t0, $a1, fin_bucle_vector

        sw $a2, ($a0)
        addi $a0, $a0, 4 # porque es un vector de words

        addi $t0, $t0, 1
        j bucle_ini_vector    # jump to bucle_ini_vector
        


        jr $ra

    show_vector:

        jr $ra


    suma_elementos:

        jr $ra

    # $a0 => direccion de inicio del vector
    # $a1 => cantidad de elementos del vector
    # $a2 => valor a buscar
    # $v0 => 
    busca_seq:

        jr $ra