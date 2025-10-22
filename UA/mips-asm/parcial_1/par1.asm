#   ------- Examen Grupo 11 -------
# 1. Realiza un programa en lenguaje ensamblador MIPS que muestre por consola la palabra escondida en
# el valor hexadecimal 0x4B4F2020. El programa cargará dicho valor en el registro $s1 y para poder
# mostrar la palabra por consola primero mostrará el carácter que hay en los bits del 8 al 15 del registro $s1,
# después mostrará el carácter que hay en los bits del 16 al 23 del registro $s1, después mostrará el carácter
# que hay en los bits del 24 al 31 del registro $s1 y para finalizar mostrará el carácter que hay en los bits del
# 0 al 7 del registro $s1.

# Cargar valor
li $s1, 0x4B4F2020

# Segunda letra (8 - 15 bits)
srl $s2, $s1, 16
andi $s2, $s2, 0x000000FF

move $a0, $s2
li $v0, 11
syscall

# Tercera letra (16 - 23 bits)
srl $s2, $s1, 8
andi $s2, $s2, 0x000000FF

move $a0, $s2
li $v0, 11
syscall

# �ltima letra (16 - 23 bits)
srl $s2, $s1, 0
andi $s2, $s2, 0x000000FF

move $a0, $s2
li $v0, 11
syscall

# Primera letra (0 - 7 bits)
srl $s2, $s1, 24
andi $s2, $s2, 0x000000FF

move $a0, $s2
li $v0, 11
syscall

# Cerrar programa
li $v0, 10
syscall
