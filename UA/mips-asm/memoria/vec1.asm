.data
    A: .word 2,4,6,8,10
    B: .word 0:4 # Vector de 4 elementos a 0
    C: .space 50 # Reserva 5 bytes
    sep: .asciiz ", "
.text
    la $s0, A # Carga la direccion del vector A en $s0
    la $s1, B # Carga la direccion del vector B en $s1
    la $s5, 5 # Tamaño del vector A
    loop: 
        add $t1, $s0, $t0
        add $t2, $s1, $t0
        addi $s2, $s2, 1
        lw $t3, 0($t1)
        
        move $a0, $t3
        li $v0, 1
        syscall
        la $a0, sep
        li $v0, 4
        syscall
        
        sw $t3, 0($t2)
        sll $t0, $s2, 2
        bne $s2, $s5, loop

    li $v0, 10
    syscall
