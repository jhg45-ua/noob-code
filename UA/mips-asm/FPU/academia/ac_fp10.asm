# distancia euclidea
.data
	coord_1: 	.float	3,   2,   3,  1.3 #a0
	coord_2:	.float  3.5, 1.3, 4, 12.3 #a1 
.text
main:	
	sub.s $f1, $f1, $f1	# suma de productos acumuladas.
	la $a0, coord_1
	la $a1, coord_2
	li $s0, 0
loop_producto:
	beq $s0, 4, end_loop
	l.s $f2, ($a0) 
	l.s $f3, ($a1)
	sub.s $f2, $f2, $f3
	mul.s $f2, $f2, $f2
	add.s $f1, $f1, $f2
	addi $s0, $s0, 1
	addi $a0, $a0, 4
	addi $a1, $a1, 4
	j loop_producto
end_loop:
	sqrt.s $f1, $f1
	mov.s $f12, $f1
	li $v0, 2
	syscall
end:
	li $v0, 10
	syscall
