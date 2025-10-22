# Este archivo contiene un programa en MIPS que suma dos vectores de números reales.
# El programa solicita al usuario que ingrese los elementos de los vectores A y B,
# y luego calcula la suma de los elementos correspondientes de ambos vectores.
# El resultado se almacena en el vector S y se imprime en la consola.

.data
    msg_A: .asciiz "Introduce los elementos del vector A:\n"
    msg_B: .asciiz "Introduce los elementos del vector B:\n"
    msg_Suma: .asciiz "Suma: "
    .align 2
    AF: .space 12
    BF: .space 12
    SF: .space 12

    N: .byte 3
    
.text
main:
    # Parte encargada del vector A
    # Imprimir mensaje de introducción del vector A
    li $v0, 4
    la $a0, msg_A
    syscall
    # Leer y guardar los numeros reales en base a N en el vector A
    la $a0, AF
    lb $a1, N
    jal read_floats
    
    # Parte encargada del vector B
    # Imprimir mensaje de introducción del vector B
    li $v0, 4
    la $a0, msg_B
    syscall
    # Leer y guardar los numeros reales en base a N en el vector B
    la $a0, BF
    lb $a1, N
    jal read_floats
    
    # Parte encargada de la suma

    la $a0, AF  # Dirección Vector A en $a0
    la $a1, BF  # Dirección Vector B en $a1
    la $a2, SF  # Dirección Vector S(uma) en $a2
    lb $a3, N   # Tamaño de los vectores en $a3
    jal add_floats

exit: 
    li $v0, 10
    syscall
    
# Funciones

# Función para sumar los elementos de dos vectores de números reales
# La función toma como parámetros la dirección de los vectores A y B,
# así como la dirección del vector S y el tamaño de los vectores.
# La suma se realiza elemento por elemento y el resultado se almacena en el vector S.
# La función también imprime el resultado de la suma en la consola.
add_floats:
	li $t0, 0 # Contador de elementos procesados
	move $t1, $a0 # Dirección del vector A
	move $t2, $a1 # Dirección del vector B
	move $t3, $a2 # Dirección del vector S(uma)
	move $t4, $a3 # Tamaño de los vectores segun N
    loop_add:
        beq $t0, $t4, end_add # Si se han procesado todos los elementos, salir del bucle
        # Cargar los elementos de los vectores A y B en registros de punto flotante
        # y sumarlos, almacenando el resultado en el vector S
        l.s $f0, ($t1)
        l.s $f1, ($t2)
        add.s $f0, $f0, $f1
        s.s $f0, ($t3)
        
        # Imprimir el resultado de la suma
        mov.s $f12, $f0
        li $v0, 2
        syscall
        
        # Imprimir un salto de línea después de cada número
        li $a0, '\n'
        li $v0, 11
        syscall 
        
        # Incrementar los punteros de los vectores A, B y S y el contador de elementos procesados 
        # para continuar con la siguiente iteración del bucle
        # Se incrementan en 4 bytes porque cada número real ocupa 4 bytes
        addi $t1, $t1, 4
        addi $t2, $t2, 4
        addi $t3, $t3, 4
        addi $t0, $t0, 1
        j loop_add
end_add:
	jr $ra
# Función para leer números reales desde la entrada estándar
# La función toma como parámetros la dirección del vector donde se almacenarán
# los números reales y el tamaño del vector.
read_floats:
    li $t0, 0
    move $t1, $a0 # Dirección del vector donde se almacenarán los números reales
    move $t2, $a1 # Tamaño del vector (N)
    loop_read:
        beq $t0, $t2, end_loop_read

        li $a0, '>'
        li $v0, 11
        syscall 

        # REAL!!!
        li $v0, 6 # Leer número real
        syscall
        s.s $f0, ($t1)

        # Incrementar el puntero del vector y el contador de elementos procesados
        addi $t1, $t1, 4
        addi $t0, $t0, 1
        j loop_read

end_loop_read:
    jr $ra