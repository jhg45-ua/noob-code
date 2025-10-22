####################################
#
#  Código ejemplo
#  Bucle while
#
####################################
.text
    li $s2, 6
    li $s5, 2

    BucleWhile: bgt $s1, $s2, SalirBucle      # Al ser while la condicion de salida es la contraria (s1 > s2)
                #slt $t0, $s2, $s1            # $t0 = 1 si $s2 < $s1, 0 de lo contrario (comprueba s1 > s2 para salir)
                #bne $t0, $zero, SalirBucle   # Ir a SalirBucle si $t0 no es 0 (s1 > s2)

                add $s1, $s1, $s5            # s1 = s1 + $s5 (cuerpo bucle)

                j BucleWhile                 # de vuelta al inicio del bucle

    SalirBucle: move $a0, $s1                # Etiqueta de salida del bucle
                li $v0, 1
                syscall
                li $v0, 10
                syscall
