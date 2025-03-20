##############################
#      Práctica 5 - EC       #
##############################
.text 0x00400000

##############################
#     Ex1 - if-then-else     #
##############################

    # Imprime indicador
    li $a0, '>'
    li $v0, 11
    syscall

    # Pide entero
    li $v0, 5
    syscall

    bgez $v0, else # Si (A >= 0) salta a eles

    sub $a0, $zero, $v0
    j exit

    else:   move $a0, $v0 # $a0 = A
    exit:   li $v0, 1
            syscall
            li $v0, 10
            syscall