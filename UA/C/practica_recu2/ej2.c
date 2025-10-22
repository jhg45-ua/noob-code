//
// Created by Julián Hinojosa Gil on 25/6/24.
//
#include <stdio.h>

void findSubmatrix(int *mat1, int *mat2, int filas, int columnas, int *res)
{
    int found = 0;

    for (int i = 0; i <= filas - 3; i++)
    {
        printf("Fila: %i ", i);
        for (int j = 0; j <= columnas - 3; j++)
        {
            printf("Columna: %i\n", i);
            found = 1;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if (mat1[(i + k) * columnas + j + l] != mat2[k * 3 + l])
                    {
                        found = 0;
                        break;
                    }
                }
                if (!found) break;
            }
            if (found)
            {
                res[0] = i;
                res[1] = j;
                return;
            }
        }
    }
    res[0] = -1;
    res[1] = -1;
}


int main(void)
{
    printf("Hello World\n");

    int mat1[4][4] = {
        {4, 6, 7, 9},
        {0, 1, 6, 6},
        {2, 3, 5, 7},
        {1, 3, 6, 2}
    };

    int mat2[3][3] = {
        {1, 6, 6},
        {3, 5, 7},
        {3, 6, 7}
    };

    int res[2];
    findSubmatrix((int *)mat1, (int *)mat2, 4, 4, res);
    printf("Result: %d %d\n", res[0], res[1]);

    return 0;
}
