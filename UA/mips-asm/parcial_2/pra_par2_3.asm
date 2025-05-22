# Programa que convierte Celsius a Fahrenheit y viceversa
# El programa solicita al usuario que elija una opción para convertir entre Celsius y Fahrenheit.
# Si elige Celsius a Fahrenheit, solicita la temperatura en Celsius y realiza la conversión.
# Si elige Fahrenheit a Celsius, solicita la temperatura en Fahrenheit y realiza la conversión.
# El programa continúa mostrando el menú hasta que el usuario elige salir.
.data
	msg1: .asciiz "1. Celsius a Fahrenheit\n2. Fahrenheit a celsius\n3. Salir\nOpcion: "
	msg_f: .asciiz "Grados Cesius a transformar: "
	msg_c: .asciiz "Grados Fahrenheit a transformar: "
	msg_error: .asciiz "\nError, elige una opcion valida\n" 
    msg_exit: .asciiz "Saliendo del programa...\n"
	k32: .float 32
	
.text
main:
    jal show_menu

    fin_programa:
        li $v0, 4
        la $a0, msg_exit
        syscall

        li $v0, 10
        syscall


# Función para mostrar el menú y manejar la entrada del usuario    
show_menu:
    # Imprime el menú de opciones
    li $v0, 4
    la $a0, msg1
    syscall
    # Solicita la opción al usuario
    li $v0, 5
    syscall
    
    beq $v0, 1, c2f # Si $v0 es 1, llama a c2f
    beq $v0, 2, f2c # Si $v0 es 2, llama a f2c
    beq $v0, 3, fin_programa # Si $v0 es 0, termina el programa
    
    # Si la opción no es válida, muestra un mensaje de error y vuelve al menú
    li $v0, 4
    la $a0, msg_error
    syscall
    
    j show_menu

# Función para convertir Celsius a Fahrenheit
c2f:
    # Mensaje para solicitar la temperatura en Celsius
    li $v0, 4
    la $a0, msg_f
    syscall
    
    li $v0, 6
    syscall # $f0 = celsius
    
    # Pasar 9 decimal a float
    li $t0, 9
    mtc1 $t0, $f9
    cvt.s.w $f9, $f9
    # Multiplicar celsius por 9
    mul.s $f0, $f0, $f9
    
    # Pasar 5 decimal a float
    li $t0, 5
    mtc1 $t0, $f5
    cvt.s.w $f5, $f5
    # Dividir celsius por 5
    div.s $f0, $f0, $f5
    # Cargar constante 32 en $f1
    l.s $f1, k32
    # Sumar 32 a la temperatura en Celsius
    add.s $f0, $f0, $f1
    
    # Imprimir el resultado
    li $v0, 2
    mov.s $f12, $f0
    syscall

    # Imprimir un salto de línea
    li $v0, 11
    li $a0, '\n'
    syscall
    
    j show_menu

# Función para convertir Fahrenheit a Celsius
f2c:
    # Mensaje para solicitar la temperatura en Fahrenheit
    li, $v0, 4 
    la $a0, msg_c
    syscall

    li $v0, 6
    syscall # $f0 = fahrenheit

    l.s $f1, k32
    sub.s $f0, $f0, $f1 # Resta 32 a la temperatura en Fahrenheit

    # Pasar 9 decimal a float
    li $t0, 9
    mtc1 $t0, $f9
    cvt.s.w $f9, $f9

    # Pasar 5 decimal a float
    li $t0, 5
    mtc1 $t0, $f5
    cvt.s.w $f5, $f5

    div.s $f1, $f9, $f5 # Dividir 9 entre 5
    div.s $f0, $f0, $f1 # Dividir la temperatura en Fahrenheit entre 9/5

    # Imprimir el resultado
    li $v0, 2
    mov.s $f12, $f0
    syscall

    # Imprimir un salto de línea
    li $v0, 11
    li $a0, '\n'
    syscall

    j show_menu