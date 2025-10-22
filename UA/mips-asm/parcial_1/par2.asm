#   ------- Examen Grupo 11 -------
# 2. Realiza un programa en MIPS que solicite, mediante un mensaje, la lectura por teclado de dos números
# cuyo valor máximo no deberá ser superior a 255. Dichos números van a definir un intervalo y el programa
# deberá verificar cuantos números del vector indicado están dentro de dicho intervalo mediante la llamada
# a una función a la que le pasamos como argumentos la dirección de memoria de comienzo del vector y los
# números introducidos. La función devolverá la cantidad de números que están dentro del rango y desde el
# programa principal se mostrará el mensaje tal y como se puede ver en el ejemplo. A continuación, el
# programa almacenará en la dirección de memoria 0x10010100 el valor calculado y finalizará.

.data
    vector: .byte 10,1,5,70,120,18,240
	# elementos: .word 7
	msj1: .asciiz "Introduce el número menor del intervalo: "
	msj2: .asciiz "Introduce el número mayor del intervalo: "
	msj3: .asciiz "Números incluidos dentro del vector: "
.text
inicio:
	# Pedir primer numero
	la $a0, msj1 # Cargar mensaje 1
	li $v0, 4
	syscall
	# Introducir numero
	li $v0, 5
	syscall
	move $a1, $v0 # $a1 = menor intervalo
	
	
	# Mensaje Pedir segundo numero
	la $a0, msj2 # Cargar mensaje 2
	li $v0, 4
	syscall
	# Introducir numero
	li $v0, 5
	syscall
	move $a2, $v0 # $a2 = mayor intervalo
	
	# Comprobaciones nuneros
	bgt $a1, 255, inicio
	bgt $a2, 255, inicio
	bgt $a1, $a2, inicio
	
	# Almacenar direccion vector
	la $a0, vector # $a0 = direccion vector
	# Cantidad elementos vector
	li $a3, 7
	#la $a3, elementos
	#lb $a3, 0($a3) # $a3 = numero elementos vector
	
	
	li $s0, 0 # Indice vector
	 
	li $v0, 0 # Contador del intervalo
	
	# Llamada a la funci�n
	jal bucle
	move $s0, $v0
	
	# Imprimir resultado
	la $a0, msj3 # Mensaje resultado
	li $v0, 4
	syscall
	move $a0, $s0
	li $v0, 1
	syscall
	# Guardar en la direccion 0x10010100
	la $a0, vector
	sb $s0, 0x10010100
	j final
bucle:
	bge $s0, $a3, fin # Condicion
	add $s1, $a0, $s0 # Desplazamiento
	lb $s2, 0($s1) # Cargar elemento
	andi $s2, $s2, 0x000000FF
	addi $s0, $s0, 1
	blt $s2, $a1, bucle
	bgt $s2, $a2, bucle
	addi $v0, $v0, 1 # Elemento dentro del intervalo
	j bucle
fin:
	jr $ra
final:
	li $v0, 10 
	syscall
