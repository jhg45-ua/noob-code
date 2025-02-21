##############################
#      Practica 2 - EC       #
##############################
.text 0x00400000

##############################
# Imprir entero por pantalla #
##############################
# addi $a0, $zero, 25 # El numero a escribir va en $a0
# addi $v0, $zero, 1 # En $v0 ponenemos el codigo de la syscall
# syscall

################################
# Leer e imprimir por pantalla #
################################
# addi $v0, $zero, 5 # Funci�on 5, read integer
# syscall

# addi $a0, $v0, 0 # Movemos el valor leido
# addi $v0, $zero, 1 # Y lo imprimimos
# syscall

# addi $v0, $zero, 10 # Funci�n exit, para acabar el programa
# syscall

##############################
#   C1 - pedir X, sacar X+1  #
##############################
# addi $v0, $zero, 5
# syscall

# addi $a0, $v0, 1
# addi $v0, $zero, 1
# syscall

# addi $v0, $zero, 10
# syscall

##############################
#   C2 - pedir X, sacar X-1  #
##############################
# addi $v0, $zero, 5
# syscall

# addi $a0, $v0, -1
# addi $v0, $zero, 1
# syscall

# addi $v0, $zero, 10
# syscall

##############################
#    Aritm�tica de enteros   #
##############################
# addiu $t0, $zero, 25
# addiu $t1, $zero, 5
# sub $t2, $t0, $t1

# addi $v0, $zero, 10
# syscall

###############################
# C8 - pedir X e Y, sacar X+Y #
###############################
# addi $v0, $zero, 5
# syscall
# addi $t0, $v0, 0
# addi $v0, $zero, 5
# syscall
# addi $t1, $v0, 0

# add $a0, $t1, $t0

# addi $v0, $zero, 1
# syscall

###############################
# C9 - pedir X e Y, sacar X-Y #
###############################
# addi $v0, $zero, 5
# syscall
# addi $t0, $v0, 0
# addi $v0, $zero, 5
# syscall
# addi $t1, $v0, 0

# sub $a0, $t0, $t1

# addi $v0, $zero, 1
# syscall

##################################
#         C10 - ORI              #
##################################
ori $t2, $zero, 7


##################################
# C14 - 0x0000FACE to 0x0000CAFE #
##################################
addiu $t0, $zero, 0x3030
xori $a0, $t0, 0x0000FACE
ori $v0, $zero, 34
syscall
