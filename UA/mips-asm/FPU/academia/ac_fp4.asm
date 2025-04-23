.data
	X: .float 4, 8, 4, 5
	W: .float 9, 4, 2, 7
	b: .float 0, 2
.text
	la $a0, X
	la $a1, W
	l.s $f12, b
	jal perceptron
	
	fin:
		li $v0, 10
		syscall
		
	perceptron:
		li $t0, 1
		sub.s $f0, $f0, $f0
		bucle_perceptron:
			bgt $t0, 4, fin_bucle
			
			
			addi $t0, $t0, 1
			j bucle_perceptron
		fin_bucle:
			jr $ra
	
	LReU:	