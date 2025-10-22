# funcion que recibe dos valores a0, a1
# devuelve la suma entre a0 a a1
.text

    # Pedimos valor de a0
    li $v0, 11
    li $a0, '?'
    syscall
    li $v0, 5
    syscall

    # Pedimos el valor de a1
    li $v0, 11
    li $a0, '?'
    syscall
    li $v0, 5
    syscall
    
    move $a0, $v0
    move $a1, $v0
    jal sumar_entre

    move $a0, $v0
    li $v0, 1
    syscall

    li $v0, 10
    syscall


sumar_entre:
    li $t0, 0 # para guardar la suma de los valores
bucle_sumer_entre:
    bgt	$a0, $a1, fin_bucle_sumar	# if $a0 > $a1 then goto fin_bucle_sumar
    add $t0, $t0, $a0
    addi $a0, $a0, 1
    j bucle_sumer_entre
fin_bucle_sumar:
    move $v0, $t0
    jr $ra