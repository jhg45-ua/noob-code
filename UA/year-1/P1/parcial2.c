#include<stdio.h>
#include<stdbool.h> //Libreria para incluir booleanos
#include<math.h> //Compilar com -lm

int pideNumero (){
		int num;

		do{
			printf("Introduce un número: ");
			scanf("%d", &num);
			if(num < 0){
				printf("Número incorrecto. ");
			}
		}while(num <0 ); //Bucle que se repetirá siempre que el número introducido sea menor que 0
		
		return num; //Devuelve el entero al main
}

void esNarcisita(int num, bool *esNarcisita, int *sumaDigitos){ //Usamos puntero para trabajar con las mismas variables declaradas en el main y poder devolver ambas
	
	//Uso 3 copias del número
	int num1 = num; //Copia del número para obtener la suma de los dígitos
	int num2 = num; //Copia que no se modifica para la comprobación final
	int countDigitos = 0;
	int digito;

	do{ //Bucle para contar el número de dígitos
		digito = num % 10; //Obtención del primer dígito
		countDigitos = countDigitos + 1;
		num = num/10; //Eliminar el último dígito del número 
	}while(num != 0);

	printf(" *El número %d tiene %d dígitos\n",num2,countDigitos);

	do{ //Bucle para obtener la suma de los dígitos elevado al número de dígitos
		digito = num1 % 10;
		*sumaDigitos = *sumaDigitos + (int)pow(digito,countDigitos);
		num1 = num1/10;
		
	}while(num1 != 0);

	if(*sumaDigitos == num2){ //Comprobación de número narcisista
		*esNarcisita = true;
	}else{
		*esNarcisita = false;
	}
	
}

void mostrarReumen(int totalNarcisistas, int totalIntroducidos){
	int porcentaje = (totalNarcisistas*100) / totalIntroducidos;

	printf("**************************************************\n");
	printf("Total de números introducidos: %d\n",totalIntroducidos);
	printf("Total de números narcisitas: %d (%d %%)\n",totalNarcisistas, porcentaje);
	printf("**************************************************\n");
}

int main(){
	
	int num;
	int totalNarcisistas = 0;
	int totalIntroducidos = 0;
	printf("**************************************************\nPROGRAMA PARA COMPROBAR SI UN NÚMERO ES NARCISISTA\n**************************************************\n\n");

	do{
		num = pideNumero();
		bool narcisita;
		int sumaDigitos = 0;
		esNarcisita(num,&narcisita,&sumaDigitos);
		
		if(num == 0){
			mostrarReumen(totalNarcisistas, totalIntroducidos);
			return 0; //Cerrar el programa 
			
		}else{
			if(narcisita == true){
				totalNarcisistas = totalNarcisistas + 1;
				printf(" *El número %d SÍ es narcisista porque la suma de sus dígitos elevado al número de dígitos es %d.\n", num, sumaDigitos);
			}else{
				printf(" *El número %d NO es narcisista porque la suma de sus dígitos elevado al número de dígitos es %d.\n", num, sumaDigitos);
		}

		totalIntroducidos = totalIntroducidos + 1;
		}

	}while(num != 0);
}