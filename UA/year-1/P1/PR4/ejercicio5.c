#include <stdio.h>
#include <stdbool.h>

/* void digitOfNum(int num, int *digit) {
	if (num == 0) return;

	digitOfNum(num / 10, digit);

	*digit = num % 10;
	digit++;
} */

bool contarCifras(int num) {
	if (num >= 1000000 && num <= 9999999)
		return true;
	else 
		return false;
}

int sumarCifrasPares(int num) {
	int sumarPares = 0, cifra;
	while (num > 0) {
		cifra = num % 10;
		if (cifra % 2 == 0)
			sumarPares += cifra;
		num /= 10;
	}
	return sumarPares;
}

int sumarCifrasImpares(int num) {
	int sumarImpares = 0, cifra;
	while (num > 0) {
		cifra = num % 10;
		if (cifra % 2 != 0)
			sumarImpares += cifra;
		num /= 10;
	}
	return sumarImpares;
}

int main() {

	int inputNum;

	do {
		printf("Introduce un numero de 7 cifras: ");
		scanf("%d", &inputNum);
	} while (!contarCifras(inputNum));

	printf("Suma cifras pares: %d\n", sumarCifrasPares(inputNum));
	printf("Suma cifras impares: %d\n", sumarCifrasImpares(inputNum));

	return 0;
}
