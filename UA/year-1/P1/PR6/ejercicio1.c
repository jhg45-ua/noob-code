#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

void check(char userInput[], int *words, int *vocals, int *con)
{
	
	int i = 0;
	while (userInput[i] != '\0') {
		if(userInput[i] == 'a' || userInput[i] == 'e' || userInput[i] == 'i' || userInput[i] == 'o' || userInput[i] == 'u' 
		|| userInput[i] == 'A' || userInput[i] == 'E' || userInput[i] == 'I' || userInput[i] == 'O' || userInput[i] == 'U')
			(*vocals)++;
		i++;
	}

	i = 0;
	while (userInput[i] != '\0') {
		if ((userInput[i] >= 'b' || userInput[i] >= 'B') && (userInput[i] <= 'z' || userInput[i] <= 'Z'))
			if (userInput[i] != 'a' || userInput[i] != 'e' || userInput[i] != 'i' || userInput[i] != 'o' || userInput[i] != 'u' 
			 || userInput[i] != 'A' || userInput[i] != 'E' || userInput[i] != 'I' || userInput[i] != 'O' || userInput[i] != 'U')
				(*con)++;
		i++;
	}
}

void askUser(char userInput[], int SIZE)
{
	if (!(strlen(userInput) >= SIZE)) {
		printf("Introduce un texto de 200 caracteres maximo: ");
		scanf("%[^\n]", userInput);
	} else
		perror("ERROR: superas el maximo permitido\n");
}

int main(void)
{
	char userText[200];
	int palabras = 0, vocales = 0, consonantes = 0;

	askUser(userText, 200);
	check(userText, &palabras, &vocales, &consonantes);
	
	printf("Texto: %s\n", userText);
	printf("* Palabras: %d\n", palabras);
	printf("* Vocales: %d\n", vocales);
	printf("* Consonantes: %d\n", consonantes);

	return EXIT_SUCCESS;
}
