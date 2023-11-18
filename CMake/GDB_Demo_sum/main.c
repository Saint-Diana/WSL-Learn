#include <stdio.h>

int main()
{
    int N = 100;
    int sum = 0;
    int i = 1;

    while (i <= N)
    {
        /* code */
        sum = sum + i;
        i = i + 1;
    }

    printf("sum = %d\nThe program is over.", sum);
    return 0;
}