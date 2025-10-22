####################################
#
#  Código ejemplo
#  Bucle FOR-WHILE
#
####################################
.text
    li $s0, 0       # Contador bucle i = 1
    li $s1, 11      # Condicion final
    li $s2, 0       # suma total

    inicio_for: bge $s0, $s1, final_for
    		#sle $t1, $s0, $s1   # $t1 = 1 si $s0 <= $s1 (i <= n)
                #beqz $t1, final_for # Ir a final_for si $t1 es 0 (i > n)

                add $s2, $s2, $s0   # total = total + i (Cuerpo del bucle)

                addi $s0, $s0, 1    # Incrementamos contador
                j inicio_for        # Volver al inicio del bucle

    final_for:  move $a0, $s2       # Etiqueta para salir del bucle
                li $v0, 1
                syscall
                li $v0, 10
                syscall
