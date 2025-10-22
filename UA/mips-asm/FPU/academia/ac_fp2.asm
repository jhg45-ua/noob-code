# el usuario mete un numero real y queremos
# mostrar por pantalla si el numero real es mayor que 10 ^^
.data
	k10:	.float 10
	leido:	.float	 0
	mensaje: .asciiz "Introduce un numero real: "
	mensaje_mayor: .asciiz "\nEl numero es mayor que 10"
	mensaje_no_mayor: .asciiz "\nEl numero no es mayor que 10"
.text
	la $a0, mensaje
	li $v0, 4		# imprimir cadena de la buena
	syscall
	la $v0, 6		# read float to $f0
	syscall
	# para comparar numeros en coma flotante se 
	# c.le	<= less or equal => guarda 1 uno en el flag 1 si se cumple
	# c.lt  <  less
	# c.eq  == equal
	l.s $f1, k10		# $f1 = M[k10] = lo que hay en esa direccion de memoria (que es un 10).
	c.le.s $f0, $f1 	# flag a 1 (true) si leido <= 10 (no es mayor)
	bc1f es_mayor		# salta si el resultado de la ultima comparacion fue falsisima :) 
no_es_mayor:
	la $a0, mensaje_no_mayor
	j fin
es_mayor:
	la $a0, mensaje_mayor
fin:
	li $v0, 4
	syscall
	
	li $v0, 10
	syscall
	