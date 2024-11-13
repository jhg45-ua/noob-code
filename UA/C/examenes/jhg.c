#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

// Prototipos
int genNumAleatorio(int min, int max);
void imprimir_tablero(int filas, int columnas, int posJugadorY, int posJugadorX, int dir, int posTesoroY, int posTesoroX, bool deugFLAG);
void avanzar(int *posJugadorY, int *posJugadorX, int dir, int filas, int columnas);
void girar(int *dir, int giros);
void jugar (int filas, int columnas, bool debugFlag);

int main(void)
{

	int opMainMenu;
	int filasTablero, columnasTablero;
	bool debugFlag = false;

	do {
		printf("Elige opción: \n");
		printf("1. Cambiar tablero\n");
		printf("2. Jugar\n");
		printf("3. Salir\n");
		printf("4. (DEBUG)\n");
		scanf("%d", &opMainMenu);

		switch (opMainMenu) {
			// Generar tablero para jugar
			case 1: 
				do {
					printf("Introduce el número de filas y columnas del tablero (mínimo 5x5): ");
					scanf("%d %d", &filasTablero, &columnasTablero);
				} while (filasTablero < 5 && columnasTablero < 5);
				break;
			// Logica de juego
			case 2: 
				jugar(filasTablero, columnasTablero, debugFlag);	
				break;
			// Salida del programa
			case 3:
				printf("Cerrando juego...\n");
				sleep(1);
				system("clear");
				break;
			// Funciones de debug
			case 4: 
				printf("--------Debug Menu--------\n");
				int opDebugMenu;
				
				do {
					printf("1. Test tablero\n");
					printf("2. Modo DEBUG general\n");
					printf("3. Salir\n");
					printf("Elige opción: ");
					scanf("%d", &opDebugMenu);
					switch (opDebugMenu) {
						case 1:
							imprimir_tablero(12, 26, 5, 10, 0, 9, 15, true);
							break;
						case 2: 
							printf("Activando modo debug...\n");
							debugFlag = true;
							break;
						case 3:
							printf("Saliendo del modo DEBUG...\n");
							sleep(1);
							system("clear");
							break;

					}
				} while (opDebugMenu != 3);
				break;
		}

	} while (opMainMenu != 3);
	return 0;
}

// Modulo extra |-> Genera numeros aleatorios en el rango [min, max]
int genNumAleatorio(int min, int max) { return rand() %  (max - min + 1) + min; }
/* Ejemplo de funcionamiento [10, 20]
 * 1. rand() genera el numero 421, entre 0 y RAND_MAX
 * 2. Se calcula el rango: 20 - 10 + 1 = 11
 * 3. Se calcula el resto 421 % 11 = 3
 * 4. Se suma el resultado al valor minimo del rango 3 + 10 = 13
*/

void imprimir_tablero(int filas, int columnas, int posJugadorY, int posJugadorX, int dir, int posTesoroY, int posTesoroX, bool debugFlag)
{
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (i == 0 || i == filas - 1 || j == 0 || j == columnas - 1)
				printf("#");
			else if (i == posJugadorY && j == posJugadorX) {
				if (dir == 0) printf("^");
				if (dir == 1) printf(">");
				if (dir == 2) printf("v");
				if (dir == 3) printf("<");
			}
			else if (debugFlag && (i == posTesoroY && j == posTesoroX))
				printf("T");
			else
				printf(" ");
		}
		printf("\n");
	}
}
/*
 * Se generar primero las filas mientras, se genera una 
 * fila entera si se trata de la primera iteracion o la ultima, luego
 * en base a las columnas (j) de la misma forma que las filas pero en el caso
 * de no cumplirse se ponen espacios
*/

void avanzar(int *posJugadorY, int *posJugadorX, int dir, int filas, int columnas)
{
	switch (dir) {
		case 0: // Mover arriba
			if (*posJugadorY > 1) (*posJugadorY)--;
			break;
		case 1: // Mover derecha
			if (*posJugadorX < columnas) (*posJugadorX)++;
			break;
		case 2: // Mover Abajo
			if (*posJugadorY < filas) (*posJugadorY)++;
			break;
		case 3: // Mover Izquierda
			if (*posJugadorX > 1) (*posJugadorX)--;
	}
}
/*
 * Se mueve segun la posicion del jugador y la direccion a la que "mira"
 *
*/

void girar(int *dir, int giros) { *dir = (*dir + giros % 4 + 4) % 4; }
/*
 * Gira de forma que siempre se queda en el rango 0 a 3
 * tanto con giros en positivo como en negoativo
*/


void jugar (int filas, int columnas, bool debugFlag)
{
	int direccion = 0; // Direccion hacia arriba

	srand(time(0));
	int jugadorX = genNumAleatorio(1, columnas - 2);
	int jugadorY = genNumAleatorio(1, filas - 2);
	int tesoroX = genNumAleatorio(1, columnas - 2);
	int tesoroY = genNumAleatorio(1, filas - 2);

	if (debugFlag) {
		printf("(DEBUG) Posición generada para el Jugador: (%d, %d)\n", jugadorX, jugadorY);
		printf("(DEBUG) Posición generada para el Tesoro: (%d, %d)\n", tesoroX, tesoroY);
	}

	int acciones = 0;
	bool encontrado = false;

	while (!encontrado) {
		// Imprime el tablero en cada turno
		imprimir_tablero(filas, columnas, jugadorY, jugadorX, direccion, tesoroY, tesoroX, debugFlag);

		int opGameMenu;
		printf("¿Qué haces? Avanzar (A/a), girar (G/g), o terminar (T/t): ");
		getchar();
		opGameMenu = getchar();

		// Primera opcion | Se pide cuanto se quiere avanzar y en el bucle for se hace hasta que se acabe
		// la distancia pedida, por cada paso se revisa si se ha encontrado el tesoro, lo que acabaria el juego.
		// Cada paso se cuenta como accion
		if (opGameMenu == 'A' || opGameMenu == 'a') {
			int distancia;
			printf("Introduce la distancia a recorrer: ");
			scanf("%d", &distancia);

			for (int i = 0; i < distancia; i++) {
				avanzar(&jugadorY, &jugadorX, direccion, filas, columnas);
				acciones++;
				if (jugadorY == tesoroY && jugadorX == tesoroX) {
					encontrado = true;
					break;
				}
			}
		} 
		// Se pide cuanto se quiere girar y se realiza el giro, cuenta como una accion
		else if (opGameMenu == 'G' || opGameMenu == 'g') {
			int giros;
			printf("Introduce el número de giros: ");
			scanf("%d", &giros);

			girar(&direccion, giros);
			acciones++;
		}

		else if (opGameMenu == 'T' || opGameMenu == 't') {
			printf("Terminaste la partida\n");
			break;
		}

		
		if (debugFlag)
			// DEBUG: se muestra la situacion del jugador
			printf("(DEBUG) Posición: (%d, %d), Dirección: %d\n", jugadorX, jugadorY, direccion);
		
	}

	if (encontrado)
		printf("¡Encontraste el tesoro en %d movimientos!\n", acciones);
	else
		printf("El tesoro estaba en (%d, %d)\n", tesoroX, tesoroY);
}
