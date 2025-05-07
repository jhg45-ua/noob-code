.data
	vector: .float 23.1, 32.5, 90.3, 231.3, 9.5, 123.5, 14.2
.text
	
	la $a0, vector	# direccion del elemento por el que voy.
	l.s $f1, ($a0)	# # el primero lo pongo en f1 (mayor encontrado hasta el momento)
	addi $a0, $a0, 4
	li $s1, 1	# cuantos elementos he evaluado
loop:
	beq $s1, 7, end
	l.s $f12, ($a0)
	mov.s $f10, $f1
	mov.s $f11, $f12
	jal get_max
	mov.s $f1, $f12
next:
	addi $s1, $s1, 1
	addi $a0, $a0, 4
	j loop
end:
	li $v0, 2
	mov.s $f12, $f1
	syscall
	
	li $v0, 10
	syscall

# $f10 => a
# $f11 => b
# $f12 => devuelve el valor mayor de a y b.
get_max:
	c.lt.s $f10, $f11
	bc1t mayor_b
mayor_a:
	mov.s $f12, $f10
	jr $ra
mayor_b:
	mov.s $f12, $f11	
	jr $ra