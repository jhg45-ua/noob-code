#include <stdio.h>
#include <stdlib.h>

int main()
{

	int i = 1, j;
	while (i <= 5) {
		if (i % 2 == 0) {
			j = 1;
			while (j <= 9) {
				printf("%d", j);
				j++;
			}
			printf("\n");
		} else {
			j = 9;
			while (j >= 1) {
				printf("%d", j);
				j--;
			}
			printf("\n");
		}
			i++;
	}

	return EXIT_SUCCESS;
}
