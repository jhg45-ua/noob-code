.data
	vector: .float 23.1, 32.5, 90.3, 231.3, 9.5, 123.5, 1234.2
	kini: .float 10.1
	kfin: .float 99.9
.text
	# Quiero contar usando la funcion definida la cantidad de valores del vector
	# que estan entre 10.1 y 99.99

	# f10 <= 10.1
	# f11 <= 99.99
	
	# li $s0, 0x4121999A
	# mtc1 $s0, $f11
	
	l.s $f10, kini
	l.s $f11, kfin
	li $s0, 0	# cuantos estan dentro del rango
	li $s1, 0	# cuantos elementos he evaluado
	la $a0, vector	# direccion del elemento por el que voy.
loop:
	beq $s1, 7, end
	l.s $f12, ($a0)
	jal cmp_in_range
	beqz $v0, next
	addi $s0, $s0, 1
next:
	addi $s1, $s1, 1
	addi $a0, $a0, 4
	j loop
end:
	li $v0, 1
	move $a0, $s0
	syscall
	
	li $v0, 10
	syscall

# $f10 => minimo
# $f11 => maximo
# $f12 => valor a comprobar
# $v0 => $f12 >= $f10 && $f12 <= $f11
cmp_in_range:
	c.lt.s $f12, $f10 # valor < minimo
	bc1t out_range
	c.lt.s $f11, $f12 # maximo < valor
	bc1t out_range

in_range:
	li $v0, 1
	jr $ra
	
out_range:
	li $v0, 0
	jr $ra