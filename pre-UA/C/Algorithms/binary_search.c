#include <stdio.h>
#include <stdlib.h>

int binarySearch(int array[], int reqNum, int low, int high)
{
    while (low <= high)
    {
        int mid = low+(high-low)/2;

        if (array[mid] == reqNum)
            return mid;
        if (array[mid] < reqNum)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main()
{
    int array[] = {3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(array)/sizeof(array[0]);

    int result = binarySearch(array, 4, 0, size-1);
    if (result == -1)
        fprintf(stderr, "Not found\n");
    else
        printf("Element found <%d> at index <%d>\n", array[result], result);

    return EXIT_SUCCESS;
}
