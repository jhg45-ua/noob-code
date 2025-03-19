#   ------- Examen Grupo 6 -------
# 2. Realiza un programa que analice los datos de la matriz dada y mediante la llamada a una función a la
# que le pasamos la dirección del vector, calcule el valor máximo y mínimo de los valores de la citada
# matriz. La función devolverá los valores máximo y mínimo y posteriormente almacenaremos el valor
# mínimo en la dirección 0x10010100 y el valor máximo en la dirección 0x10010103. Para finalizar , el
# programa mostrará los datos.

.data
    matrix: .byte   2,      5,      9,
                    110,    14,     18,
                    21,     33,     5


.text
    li $t0, 1 # contador
    la $a0, matrix
    lb $t1, ($a0) # menor
    lb $t2, ($a0) # mayor


    bucle: 
        bgt $t0, 9, fin_bucle # se acaba cuando $t0 es mayor que los elementos de la matriz
        
        lb $t3, ($a0)
        bgt $t3, $t2, ac_mayor
        j comp_menor
        ac_mayor:
            move $t2, $t3
        comp_menor:
            blt $t3, $t1, ac_menor
            j seguir
        ac_menor: 
            move $t1, $t3
        seguir:
            addi $t0, $t0, 1
            j bucle
    fin_bucle:  
        li $v0, 10
        syscall
    
