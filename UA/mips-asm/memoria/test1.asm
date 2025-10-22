.data 
	A: .word 6
	B: .word 8
	C: .space 4
.text 
	la $t0, A
	lw $t1, 0($t0)	# Direccionamiento indirecto - A
	lw $t2, 4($t0) # Direccionamiento relativo - B

	add $t3, $t2, $t1

	sw $t3, C