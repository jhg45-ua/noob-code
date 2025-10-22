##############################
#      Práctica 3 - EC       #
##############################
.text 0x00400000

	#sub $t0, $t1, $t2
    
    ## Cargar dato de 32 bits - 0x12345678
    # Una forma: li x, 0x12345678
    # Otra forma y lo que hace la pseudo instruccion li
    # lui x, 0x1234
    # ori x, $zero, 0x5678
    
##############################
#     C2 - escribir codigo   #
##############################
	#li $t0, 5
	#addi $t1, $t0, 10
	#subi $t2, $t1, 30
	
	
##############################
#   C4 - Programa ECHO Mod   #
##############################
	#li $a0, '>' 
	#li $v0, 11
	#syscall
	
	#li $v0,12 #Función 12. Read character
	#syscall #Carácter leído en $v0
	#move $t0,$v0 #Carácter a escribir en $a0
	
	#li $a0, '\n'
	#li $v0, 11
	#syscall
	
	#move $a0,$t0 #Carácter a escribir en $a0
	#li $v0,11 #Función 11. Print character
	#syscall
	
	#li $v0, 10 #Función 10. Acaba programa
	#syscall
	
##############################
#   C6 - Decimal to ASCII    #
##############################
	li $a0, '~'
	li $v0, 11
	syscall
	
	li $v0, 5
	syscall
	move $t0, $v0
	
	li $a0, '\n'
	li $v0, 11
	syscall
	
	
	