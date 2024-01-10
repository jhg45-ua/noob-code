#include <stdio.h>

int main(int argc, char const *argv[])
{
    int op;

    printf("Choose an option: ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        printf("Case 1\n");
        break;
    case 2:
        printf("Case 2\n");
    default:
        return 0;
        break;
    }

    return 0;
}
