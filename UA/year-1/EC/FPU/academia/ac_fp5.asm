# PROPUESTO COMPLETAR EL MAIN Y COMPLETAR LA FUNCION DE TRANFORMACION.

# · Crea una función que reciba como primer parámetro un entero que represente milisegundos y como segundo un valor
# de 0 a 2 que indica lo siguiente:
# • 0: convierte el primer parámetro a segundos.
# • 1: convierte el segundo parámetro a minutos.
# • 2: convierte el tercer parámetro a horas.
# · Deberá realizar la conversión en coma flotante.

# Añade el código necesario para probar el funcionamiento:
# 1. Realiza un bucle de 3 iteraciones de 0 a 2.
# 2. Llama a la función con el valor de la variable DNI como primer parámetro y la iteración como segundo
# parámetro.
# 3. Muestra el resultado por consola mostrando un mensaje que indique si se trata de horas, minutos o segundos.
.data
	dni_int: 	.word 484312343		# esto esta en C2
	dni_float:	.float 484312343	# esto esta codificado en ieee
	k_mili:		.float 1000
	k_mins:		.float 60000
	k_horas:	.float 360000
.text

	# hay que hacer un bucle con 3 iteraciones 0, 1 y 2
	# llamar a la funcion con el contador del bucle e imprimir
	# por pantalla el valor devuelto.	

	li $v0, 10
	syscall

# $a0 <= entero milisegundos.
# $a1 <= operacion a realizar.
cvt_time:
	beq $a1, 0, opcion_0
	beq $a1, 1, opcion_1
	beq $a1, 2, opcion_2
default:
	# si tuviera que hacer algo en caso de que no sea ninguna opcion de las anteriores!
	j next_cvt_time

opcion_0: # segundos
	# completar
	j next_cvt_time
	
opcion_1: # minutos
	# completar
	j next_cvt_time
	
opcion_2: # horas
	# completar
	j next_cvt_time

next_cvt_time:
	jr $ra
	
