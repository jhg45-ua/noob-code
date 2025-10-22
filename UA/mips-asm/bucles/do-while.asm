####################################
#
#  Código ejemplo
#  Bucle DO-WHILE
#
####################################
.text
    li $s0, 1       # Contador del bucle
    li $s1, 11      # condicion final
    li $s2, 0       # suma total

    inicio_do_while:

                add $s2, $s2, $s0  # total = total + i (cuarpo bucle)

                addi $s0, $s0, 1  # incrementar contador i++
                blt $s0, $s1, inicio_do_while # Lo mismo pero más sencillo
                #slt $t1, $s0, $s1  # $t1 = 1 si $s0 < $s1 (i < n)
                #bne $t1, $zero, inicio_do_while # Ir a inicio_do_while si $t1 no es 0 (i < n)

    final_do_while: move $a0, $s2         # Etiqueta de salida
                    li $v0, 1
                    syscall 
                    li $v0, 10
                    syscall
