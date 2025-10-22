.data
    matrix: .byte 1,  4,  7,
            	  2,  5,  8,
            	  3,  6,  9
                  
    columnas: .word 3
.text
    la $t0, matrix
    # li $t3, 3
    lw $t3, columnas
    li $t2, 0   # Indice matrix

    bucle: 
        lb $t1, 0($t0)
        move $a0, $t1
        jal imprim

        lb $t1, 3($t0)
        move $a0, $t1
        jal imprim

        lb $t1, 6($t0)
        move $a0, $t1
        jal imprim

        jal new_line

        addi $t2, $t2, 1
        addi $t0, $t0, 1
        bne $t2, $t3, bucle
    
    li $v0, 10
    syscall

    imprim:
        li $v0, 1
        syscall
        li $a0, '\t'
        li $v0, 11
        syscall
        jr $ra

    new_line:
        li $a0, '\n'
        li $v0, 11
        syscall
        jr $ra
