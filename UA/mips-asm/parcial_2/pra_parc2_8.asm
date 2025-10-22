.data
    matrizA:	.word	2, 3, 1, 
                        3, 2, 1, 
                        3, 2, 1
    matrizB:	.float  0.5, 1.4, 2.3, 
                        0.1, 0.2, 0.3, 
                        1.1, 1.2, 1.3
    matrizR:	.space	36 # Matriz de 3x3 para floats (4 bytes por float)
    k2:		.float 2

.text
main:
    # Imprimir matrizA
    la $a0, matrizA
    jal impE

    # Imprimir matrizB
    la $a0, matrizB
    jal impF

    # Calcular matrizR = promedio(matrizA, matrizB)
    la $a0, matrizA
    la $a1, matrizB
    la $a2, matrizR
    jal sumaCosas

    # Imprimir matrizR
    la $a0, matrizR
    jal impF

    # Salir
    li $v0, 10
    syscall

# $a0 <= matrizA
# $a1 <= matrizB
# $a2 <= matrizR
sumaCosas:
    li $t0, 0 # contador de iteraciones
    move $t1, $a0		# $t1 por donde voy en mA
    move $t2, $a1		# $t2 por donde voy en mB.
    move $t4, $a2       # $t4 por donde voy en mR.
    li $t3, 0		# iteraciones realizadas.
    l.s $f2, k2		# $f2 = 2.0
loopSumaCosas:
    beq $t0, 9, end_sumaCosas

    lw $t6, ($t1)         # leer entero de matrizA
    mtc1 $t6, $f0         # mover a registro flotante
    cvt.s.w $f0, $f0      # convertir a float

    l.s $f1, ($t2)		# leer float de matrizB

    add.s $f0, $f0, $f1	# sumar
    div.s $f0, $f0, $f2	# dividir entre 2

    s.s $f0, ($t4)        # guardar en matrizR

    addi $t0, $t0, 1
    addi $t1, $t1, 4
    addi $t2, $t2, 4
    addi $t4, $t4, 4
    j loopSumaCosas
end_sumaCosas:
    jr $ra

# $a0 la direccion de la matriz.
impE:
    li $t0, 0		# contador de veces
    move $t1, $a0		# $t1 <= direccion del elemento
    li $t3, 0		# contador de columnas
loop_impE:
    beq $t0, 9, end_impE	# cuando llego a 9, me salgo
    lw $a0, ($t1)		# leo el elemento de la memoria.
    li $v0, 1
    syscall			# imprimir entero
    li $a0, ' '		
    li $v0, 11
    syscall			# imprimir espacio
    
    addi $t3, $t3, 1
    bne $t3, 3, next_jon
    li $t3, 0
    li $a0, '\n'
    li $v0, 11
    syscall
next_jon:
    addi $t0, $t0, 1
    addi $t1, $t1, 4
    j loop_impE
end_impE:
    jr $ra

impF:
    li $t0, 0
    move $t1, $a0
    li $t3, 0
loop_impF:
    beq $t0, 9, end_impF
    l.s $f12, ($t1)
    li $v0, 2
    syscall
    li $a0, ' '
    li $v0, 11
    syscall
    
    addi $t3, $t3, 1
    bne $t3, 3, nextF
    li $t3, 0
    li $a0, '\n'
    li $v0, 11
    syscall
nextF:
    addi $t0, $t0, 1
    addi $t1, $t1, 4
    j loop_impF
end_impF:
    jr $ra