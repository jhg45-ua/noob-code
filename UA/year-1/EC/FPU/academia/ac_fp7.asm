# Programa que pide dos numeros reales y muestra por pantalla el mayor
.data

.text
	li $v0, 11
	li $a0, '>'
	syscall
	
	li $v0, 6
	syscall		# cin >> $f0
	mov.s $f1, $f0
	
	li $v0, 11
	li $a0, '>'
	syscall
	
	li $v0, 6
	syscall		# cin >> $f0
	mov.s $f2, $f0

	c.lt.s $f1, $f2
	bc1t mayor_f2

mayor_f1:	
	mov.s $f12, $f1	
	j print_mayor

mayor_f2:
	mov.s $f12, $f2

print_mayor:
	li $v0, 2
	syscall
	
	li $v0, 10
	syscall

