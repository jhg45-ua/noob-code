.text 0x00400000
    # Practica 4. Ejercicio 1.
    # ¿Con qué instrucciones traducirá el ensamblador
    # las pseudoinstrucciones rol y ror?. Escribe un
    # código sencillo de prueba de ambos operadores y
    # ensámblalos para comprobarlo.

########################################################
    # Test 1.
    # ¿Que hay en el registro $t1, despues de realizar la rotacion?
    # rol => rotacion a la izquierda.
    li $t1, 0xABCD7654
    rol $t1, $t1, 4     # $t1 = BCD7 654A
    li $v0, 34
    move $a0, $t1
    syscall
    # Respuesta: # $t1 = BCD7 654A

#######################################################
    # Test 2.
    # Dado el siguiente codigo, a que instruccion rol corresponderia
    li $9, 0xABCD7654
    srl $1, $9, 0x1c # mando lo que voy a perder a la derecha 32 - 4 = 28
    # $1 = 0x0000 000A
    sll $9, $9, 0x04 # rol, perdiendo los 4 primeros bits
    # $9 = BCD7 6540
    or $9, $9, $1

    # Respuesta: rol $9, $9, 4

    ######################################################
    # Test 3.
    # Que numero imprime por pantalla el siguiente codigo.
    li $t1, 0xFFFFFFF8
    sra $t1, $t1, 2 # 1000 => 1110 => 0xFFFF FFFE
    li $v0, 1
    addu $a0, $zero, $t1
    syscall
    # Por cada desplazamiento que haga a la derecha hago una
    # division por 2
    # Respuesta -2

    ##################################################
    # Test 4.
    # Que numero imprime por pantalla el siguiente codigo.
    li $t1, 0x10
    sra $t1, $t1, 2 # 1000 => 1110 => 0x04
    li $v0, 1
    addu $a0, $zero, $t1
    syscall

    li $v0, 10
    syscall
    # partimos del 16
    # 1 0000
    # Respuesta: 4

    ###########################################
    # Test 5.
    # ¿Cual es el contenido del registros
    #   rs = 0
    #   rt = 11 ($t3)
    #   rd = 9 ($t1)
    #   shmt = 0101 => aqui almacena el desplazamiento!!

    # Para la instruccion siguiente si $t0 es $8?
    sll $t1, $t3, 5 # sll rd, rt, shamt

    # Respuesta
    #   Tipo R
    #
    #   cop     rs      rt    rd      shmt     func
    #   000000 00000  01011  01001    00101   000000

    # 0x000b4940
    #
    #   0000 0000 0000 1011 0100 1001 0100 0000

#############################################################
    # Test 6.
    # Dada la siguiente instruccion
    # add $t0, $t1, $t2
    # Que se almacenaria en el campo
    # rs, rt y rd a la hora de codificar la instruccion
    # sabiendo que $t0 es el registro 8 del banco de registros.?
    #
    # Respuesta
    #   Tipo R = cop Rs Rt Rd shmt func
    #   rs = 01001
    #   rt = 01010
    #   rd = 01000
    #

############################################################
    # Test 7.
    # Dada la siguiente instruccion ($t0 equiv. $8)
    # addi $t2, $t6, 10
    # elige:
    # a)
    #   rs = 01110
    #   rd = 01010
    #   datoI = 0x000A
    # b)
    #   rs = 01110
    #   rt = 01010
    #   datoI = 0x000A
###########################################################
    # Respuesta TIPO I: cop Rs Rt desp
    # b)


########################################################
# Test 8.
# Dado el siguiente codigo, ¿Que instrucciones tendriamos
# que añadir para que se multplique por 10?

mult10:
    sll $v0, $a0, 2 #Función multiplica entero por 4

# a)
    add $v0, $v0, $v0 # x4 + x4 = x8
    add $v0, $v0, $a0
    add $v0, $v0, $a0
    jr $ra

################################################
    # Test 9.
    # Multiplicar $a0 x 18 y dejar el resultado en $v0
    sll $v0, $a0, 4     #  x 2^4
    sll $v1, $a0, 1     #  x 2
    add $v0, $v0, $v1

    ###############################################3
    # Test 10
    # Que almacena finalmente el registro $v0

    sll $v0, $a0, 2
    sll $v1, $a0, 3
    add $v0, $v0, $v1
    add $v0, $v0, $a0

    # Respuesta
    # sll $v0, $a0, 2   => $v0 = 4 x $a0
    # sll $v1, $a0, 3   => $v1 = 8 x $a0
    # add $v0, $v0, $v1 => $v0 = 12 x $a0
    # add $v0, $v0, $a0 => $v0 = 13 x $a0

#################################################
    # Test  11
    # Dado el siguiente codigo:
    li $a0, 12
    li $a1, 14
    jal funcion     # en $ra = siguiente instruccion
                    # en $pc = direccion de funcion
    move $a0, $v0 # para conservar el valor devuelto
    # Ademas aprovecho para pasar el argumento a syscall.
    li $v0, 4
    syscall
    li $v0, 10
    syscall
funcion:
    add $v0, $a0, $a1
    jr $ra # $pc = $ra

    # Que imprime por pantalla?

    # Que se guarda en el registro $ra?
    #  SOL: En $ra se guarda la direccion de la siguiente instruccion,
    # para poder volver a esa insturccion modificando jump register $ra

################################################
    # Test 12
    # Hay un problema en este programa, donde esta?

    li $a0, 12
    li $a1, 14
    jal funcion
    li $v0, 4
    move $a0, $v0
    syscall

    # Respuesta: Estoy chafando el valor devuelto con
    # el numero de servicio.

    # Todos los loads que no superan los 16 bits
    # se traducen a addiu (no extienden signo)
    li $t3, 0x40
    # Equivalente V
    addiu $t3, $zero, 0x40

    li $t4, 0x80
    # Equivalente V
    addiu $t4, $zero, 0x30

    # Si un load supera los 16 bits usa upper-inmediate (lui) y ori
    li $t1, 0x89ABCDEF
    # Equivalente V
    lui $t1, 0x89AB
    ori $t1, $t1, 0xCDEF


    addi $t1, $zero, 0x80   # resultado positivo
    subi $t1, $zero, 0x80   # resultado negativo
    # $t1 = 0xFFFF FF80

    # addi vs addiu
    # ambas operaciones se hacen en c2, independientemente
    # de su signo (u), la unica diferencia es el overflow.

    addiu $t1, $zero, 0x80000000
    # addi $t1, $t1, 0x80000000 # Arithmetic overflow
    addiu $t1, $t1, 0x80000000 # $t1 = 0


    # desplazamientos y rotaciones nazis.
    li $t1, 0xabcd0707
    rol $t1, $t1, 4



    li $v0, 10
    syscall
