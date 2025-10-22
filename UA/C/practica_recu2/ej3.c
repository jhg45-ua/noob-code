//
// Created by Julián Hinojosa Gil on 26/6/24.
//
#include <stdio.h>

void bubble_sort(int array[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j+1])
            {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

void printArray(int array[], int size)
{
    for (int i  = 0; i < size; i++)
        printf("%d, ", array[i]);
}

int main(void)
{
    int array[] = {9, 1, 8, 2, 7, 3, 6, 4, 5};
    printf("Hello World\n");

    int size = sizeof(array)/ sizeof(array[0]);

    bubble_sort(array, size);
    printArray(array, size);

    return 0;
}