# Programa que obtiene una cadena de caracteres y elimina los caracteres pedidos

.data
    cadena: .asciiz "aasilomaars"
    
.text
main:
    la $a0, cadena
    li $a1, 'a'
    jal borrar_caracter
    la $a0, cadena
    li $v0, 4
    syscall
    li $v0, 10
    syscall
    
	fin:
		li $v0, 10
		syscall
    
borrar_caracter:
    move $t0, $a0        # $t0 = puntero de lectura
    move $t1, $a0        # $t1 = puntero de escritura
borrar_loop:
    lb $t2, ($t0)       # cargar byte actual
    beqz $t2, fin_borrar # si es fin de cadena, terminar
    beq $t2, $a1, skip   # si es el caracter a borrar, saltar escritura
    sb $t2, ($t1)       # escribir caracter en nueva posición
    addiu $t1, $t1, 1    # avanzar puntero de escritura
skip:
    addiu $t0, $t0, 1    # avanzar puntero de lectura
    j borrar_loop
fin_borrar:
    sb $zero, ($t1)     # terminar la cadena con null
    jr $ra