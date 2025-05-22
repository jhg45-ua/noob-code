# Pasar 200 asciiz a decimal
# El programa convierte una cadena de caracteres que representa un número decimal en su representación numérica 
# y luego lo convierte de nuevo a una cadena de caracteres. 
# Finalmente, imprime la cadena resultante.
.data
	cad_num: .asciiz "112"
	cad_res: .space 30 # Resultado no tendra mas de 30 bytes
    msg_1:   .asciiz "Cadena a entero: \n"
    msg_2:   .asciiz "\nEntero a cadena: \n"
	
.text
    li $v0, 4
    la $a0, msg_1
    syscall

	la $t0, cad_num		# Cadena a transformar
	li $t1, 0		    # Resultado de numero transformado
    # El bucle convierte la cadena de caracteres a un número decimal
    inicio_to_num:
        lb $t2, ($t0)
        beqz $t2, fin_to_num
        
        # El bucle convierte el caracter a su valor numerico
        sll $t3, $t1, 1		# Multiplicamos por 2 en $t3
        sll $t4, $t1, 3		# Multiplicamos por 8 en $t4
        add $t1, $t3, $t4	# Con la suma de ambos multiplicamos por 10 en $t1
        subi $t2, $t2, '0'	# '1' => 1 Pasamos de ascii a decimal restando '0'
        add $t1, $t1, $t2	# Sumamos el valor numerico al resultado
        
        # Avanzamos al siguiente caracter 1 byte 
        addi $t0, $t0, 1
        j inicio_to_num
        
    fin_to_num:
        # Imprimimos el resultado
        li $v0, 1
        move $a0, $t1
        syscall

    li $v0, 4
    la $a0, msg_2
    syscall 
    # El numero esta en t1 y el resultado hay que almacenarlo en cad_res
    itoa:
        la $t0, cad_res
        li $t2, 10 # Constante 10 para dividir
        loop_itoa:
            beqz $t1, end_loop_itoa
            
            # Dividimos el numero entre 10 y guardamos el resto
            # El cociente se guarda en $t1 y el resto en $t3
            div $t1, $t2		# hi=$t1 mod $t2 ; lo=$t1 div $t2
            mfhi $t3		    # Resto de la division
            addi $t3, $t3, '0'  # Pasamos a ascii 
            sb $t3, ($t0)
            mflo $t1		    # Cociente a $t1
            
            addi $t0, $t0, 1 # Siguiente caracter de la cadena
            j loop_itoa
        end_loop_itoa:
            li $t2, 0
            sb $t2, ($t0)
            
        # Ahora se le da la vuelta a la cadena resultante
            subi $t0, $t0, 1
            la $t1, cad_res
    reverse:
        bge $t1, $t0, end_reverse
        lb $t2, ($t0)
        lb $t3, ($t1)
        
        sb $t3, ($t0)
        sb $t2, ($t1)
        
        addi $t1, $t1, 1
        subi $t0, $t0, 1
        
        j reverse

    end_reverse:
        li $v0, 4
        la $a0, cad_res
        syscall

    fin_de_programa:
        li $v0, 10
        syscall
