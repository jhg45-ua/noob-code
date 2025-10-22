#include <stdio.h>

int main()
{
	int i = 1;

	while (i <= 5) {
		int j = 1;
		while (j <= 5) {
			printf("%d", j);
			j++;
		}
		printf(" ");
		
		j = 1;
		while (j <= 5) {
			if (i == j)
				printf("%d", i);
			else
				printf("*");
			j++;
		}
		printf("\n");
		i++;
	}

	return 0;
}
