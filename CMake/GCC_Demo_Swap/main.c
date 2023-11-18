#include <stdio.h>
#include "swap.h"

int main()
{
    int a = 10, b = 30;
    swap(&a, &b);
    printf("after swap, a = %d, b = %d\n", a, b);
    return 0;
}