#   ------- Examen Grupo 6 -------
# 1. Realiza un programa en lenguaje ensamblador MIPS que solicite al usuario (por consola) que
# introduzca dos números (comprendido entre 0 y 255) y muestre por consola los números impares que hay
# en el intervalo comprendido entre los números introducidos. 

.data
    msg1: .asciiz "Introduce el menor: "
    msg2: .asciiz "Introduce el mayor: "


.text
    pedir_menor: 
        la $a0, msg1 # Dir msg1
        li $v0, 4
        syscall
        li $v0, 5
        syscall

        bltz $v0, pedir_menor
        bgt $v0, 255, pedir_menor
        move $s0, $v0
    pedir_mayor:
        la $a0, msg2 # Dir msg1
        li $v0, 4
        syscall
        li $v0, 5
        syscall

        bltz $v0, pedir_mayor
        bgt $v0, 255, pedir_mayor
        move $s1, $v0

    bucle_impares:
        bgt $s0, $s1, fin_bucle_impares # si $menor es mas que $mayor -> fin
        andi $s2, $s0, 1
        beqz $s2, next
        li $v0, 1
        move $a0, $s0
        syscall
        li $v0, 11
        li $v0, ' '
        syscall
        next:
            addi $s0, $s0, 1
            j bucle_impares

        addi $s0, $s0, 1
        j bucle_impares

    fin_bucle_impares:



