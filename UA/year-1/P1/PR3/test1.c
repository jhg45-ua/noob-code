#include <stdio.h>

int main() 
{
	int i = 1;
	while (i <= 8) {
		printf("%d => ", i);
		int j = 1;
		while (j <= 8) {
			printf("(%d, %d) ", i, j);
			j++;
		}
		printf("\n");
		i++;
	}

	return 0;
}
