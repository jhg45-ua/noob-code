.data
    .byte 12, 32, 1, 12     # 1byte = 8bits
    .half 3, 4              # 16 bits
    .word -44               # 32 bits
    cadena: .asciiz "Introduce un numero: " # La cadena guarda en memoria cada caracter con su numero ascii

.text 0x0040000

    # La ISA MIPS tiene 32 registros de 32bits

    # Imprimir cadena
    # li $v0, 4   # Otra forma de inicializar registros
    addi $v0, $zero, 4
    la $v0, cadena      # load address, carga en $a0, la direccion de comienzo de la cadena
    syscall

    # Pedir nuemro
    addi $v0, $zero, 5
    syscall
    addi $s0, $v0, 0

    # Pedir otro numero con mensaje
    # li $v0, 4   # Otra forma de inicializar registros
    addi $v0, $zero, 4
    la $v0, cadena      # load address, carga en $a0, la direccion de comienzo de la cadena
    syscall

    # Pedir nuemro
    addi $v0, $zero, 5
    syscall
    addi $s1, $v0, 0

    # Imprimir la suma de dos enteros
    add $s2, $s0, $s0
    addi $a0, $s2, 0
    addi $v0, $zero, 1
    syscall
