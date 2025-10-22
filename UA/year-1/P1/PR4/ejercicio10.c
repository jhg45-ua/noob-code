#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función que genera una carta aleatoria entre 1 y 10
int generarCarta() { return 1 + rand() % 10; }

// Función que muestra la carta según su valor
void mostrarCarta(int cartaObtenida) 
{
    	if (cartaObtenida == 1)
        	printf("(%d) AS", cartaObtenida);
    	else if (cartaObtenida == 8)
        	printf("(%d) SOTA", cartaObtenida);
    	else if (cartaObtenida == 9)
        	printf("(%d) CABALLO", cartaObtenida);
    	else if (cartaObtenida == 10)
        	printf("(%d) REY", cartaObtenida);
    	else
        	printf("%d", cartaObtenida);
}

// Función que actualiza la puntuación según el valor de la carta
void actualizarPuntuacion(float *puntJugador, int cartaObtenida) 
{
    	if (cartaObtenida == 1 || cartaObtenida == 8 || cartaObtenida == 9 || cartaObtenida == 10)
        	*puntJugador += 0.5; // Las figuras suman 0.5
    	else
        	*puntJugador += cartaObtenida; // Las demás cartas suman su valor
}

int main() 
{
    	int cartaObtenida;
    	float puntJugador = 0, puntBanca = 0;

    	// Inicializar la semilla de números aleatorios
    	srand(time(NULL));

    	printf("Pulsa Intro para empezar a jugar...\n");
    	getchar(); // Esperar a que el usuario pulse Enter

	// Ciclo principal del juego
    	while (1) 
    	{
        	// Turno de la banca
        	printf("=======================\n");
        	cartaObtenida = generarCarta();
        	actualizarPuntuacion(&puntBanca, cartaObtenida);
        	printf("Carta para la banca: ");
        	mostrarCarta(cartaObtenida);
        	printf(" => Puntuación %.2f\n", puntBanca);

        	// Verificar si la banca se ha pasado de 7.5
        	if (puntBanca > 7.5) 
		{
            	printf("La banca se ha pasado de 7.5. ¡Has ganado!\n");
	    	break;
        	}

        	// Turno del jugador
        	cartaObtenida = generarCarta();
        	actualizarPuntuacion(&puntJugador, cartaObtenida);
        	printf("Carta para el jugador: ");
        	mostrarCarta(cartaObtenida);
        	printf(" => Puntuación %.2f\n", puntJugador);

        	// Verificar si el jugador se ha pasado de 7.5
        	if (puntJugador > 7.5) 
		{
            	printf("Te has pasado de 7.5. ¡La banca ha ganado!\n");
            	break;
        	}

		// Esperar a que el jugador pulse una tecla para la siguiente ronda
        	printf("\nPulsa Enter para la siguiente ronda...\n");
        	getchar(); // Espera a que el jugador pulse una tecl
    	}

    	return 0;
}
