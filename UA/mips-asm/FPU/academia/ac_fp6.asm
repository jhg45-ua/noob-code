.data
	nombre: .space 100
	N:	.word 0
	vector:	.space 400	 # hasta 100 numeros reales
	msg_nombre:	.asciiz "\nIntroduce tu nombre y apellidos: "
	msg_tam:	.asciiz "\nIntroduce el tamaño del vector: "
	msg_prompt:	.asciiz "\?: "
.text
	jal leer_datos
	
	li $v0, 10
	syscall
	
# $a0 <= recibe la direccion de cominzo del nombre
# $v0 <= numero de caracteres de la cadena que no son espacios
contar_caracteres:

	jr $ra
	
leer_datos:
	# leer una cadena y almaenarla en nombre
	
	
	# leer un entero positivo y mmenor que 100 y almacenarlo en N
	
	
	# leer N elementos y guardarlos en vector
	
	
	jr $ra
