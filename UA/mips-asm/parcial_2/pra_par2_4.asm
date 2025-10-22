# Progrma que lee un nombre y un vector de reales
# y cuenta el numero de caracteres que no son espacios

.data
    # Definicion de variables
    vector_reales: .space 400 # Espacio para 100 reales maximo (4 bytes cada uno)
    N: .word 0 # Espacio para el tamaño del vector
	nombre: .space 110
    # Definicion de mensajes
    msg_tam:	.asciiz "\nIntroduce el tamaño del vector: "
    msg_vector:	.asciiz "\nContenido del vector: "
	msg_nombre:	.asciiz "\nIntroduce tu nombre y apellidos: "
	msg_resultado: .asciiz "Numero de caracteres (sin espacios): "
    msg_prompt:	.asciiz "\?: "
.text
main:
    # leer el nombre y el tamaño del vector
    jal leer_datos
	
    # Pasar la dirección de nombre a $a0 para contar caracteres
    la $a0, nombre
    jal contar_caracteres

    # Mostrar el resultado
    move $t0, $v0  # Guardar el resultado en $t0
    li $v0, 4
    la $a0, msg_resultado
    syscall

    # Numero de caracteres
    li $v0, 1
    move $a0, $t0
    syscall

    jal leer_reales # Leer el tamaño del vector y los reales
    jal imprim_vector # Imprimir el vector de reales

    salir_programa: 
        li $v0, 10
        syscall

# Funciones

# contar_caracteres: cuenta el numero de caracteres que no son espacios
# $a0 <= recibe la direccion de cominzo del nombre
contar_caracteres:
    li $t0, 0           # Contador de caracteres que no son espacios
    move $t1, $a0       # Dirección actual del carácter
    bucle_contar_caracteres:
        lb $t2, ($t1)      # Cargar el carácter actual
        beq $t2, '\n' fin_bucle_contar_caracteres   # Si es fin de cadena, termina
        beq $t2, ' ', siguiente                     # Si es espacio, no contar
        addi $t0, $t0, 1   # Si NO es espacio, incrementar contador
    siguiente:
        addi $t1, $t1, 1   # Siguiente carácter
        j bucle_contar_caracteres
    fin_bucle_contar_caracteres:
        # Por convencion, el resultado se devuelve en $v0 y no en $t0
        move $v0, $t0
        jr $ra

# leer_datos: lee el nombre y lo almacena en la variable nombre
leer_datos:
	# leer una cadena y almaenarla en nombre
	li $v0, 4
	la $a0, msg_nombre
	syscall
	
    # leer el nombre y apellidos
	li $v0, 8 # syscall leer cadena
	la $a0, nombre # Donde se almacenara el nombre
	li $a1, 99  # Tamaño maximo de la cadena
	syscall
    jr $ra

# leer_reales: leer un entero positivo meyor que 0 y mmenor que 100 y almacenarlo en N 
# para determinar el tamaño del vector de reales
# y luego almacenar los reales en el vector
leer_reales:
    # leer el tamaño del vector
    li $v0, 4
    la $a0, msg_tam
    syscall
    
    # leer el tamaño del vector
    li $v0, 5 # syscall leer entero
    syscall
    
    # comprobar que el entero es menor que 100
    bge $v0, 100, leer_reales
    # comprobar que el entero es mayor que 0
    blt $v0, 0, leer_reales

    # almacenar el tamaño del vector en N
    sw $v0, N # Almacenar el tamaño del vector

    li $t0, 0 # Inicializar el contador bucle_vector_reales
    lw $t1, N # Cargar el tamaño del vector en $t1
    la $t2, vector_reales # Cargar la dirección del vector en $t2
    bucle_vector_reales:
        beq $t0, $t1, fin_bucle_vector_reales # Si el contador es igual al tamaño del vector, salir

        li $v0, 4
        la $a0, msg_prompt
        syscall

        # leer un real, se guarda en $f0
        li $v0, 6 
        syscall 
        s.s $f0, ($t2) # Almacenar el número en el vector

        addi $t0, $t0, 1 # Incrementar el contador
        addi $t2, $t2, 4 # Pasar a la siguiente posición del vector
        j bucle_vector_reales # Volver al inicio del bucle

        fin_bucle_vector_reales:
            jr $ra # Volver al programa principal


# imprim_vector: Mostrar el vector de reales
imprim_vector:
    li $v0, 4
    la $a0, msg_vector
    syscall

    li $t0, 0 # Inicializar el contador bucle_imprimir_vector
    lw $t1, N # Cargar el tamaño del vector en $t0
    la $t2, vector_reales # Cargar la dirección del vector en $t2
    bucle_imprim:
        beq $t0, $t1, fin_bucle_imprim # Si el contador es igual al tamaño del vector, salir

        # cargar el real en $f0
        l.s $f0, ($t2) # Cargar el número en $f0

        # imprimir el real
        mov.s $f12, $f0 # Mover el número a $f12
        li $v0, 2
        syscall

        # imprimir espacio en blanco
        li $v0, 11
        li $a0, ' '
        syscall

        addi $t0, $t0, 1 # Incrementar el contador
        addi $t2, $t2, 4 # Pasar a la siguiente posición del vector
        j bucle_imprim # Volver al inicio del bucle

        fin_bucle_imprim:
            jr $ra # Volver al programa principal