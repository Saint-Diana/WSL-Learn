#include <iostream>
#include "swap.h"

int main(int argc, char const *argv[])
{
    Swap swap(10, 20);
    printf("Before Swap, ");
    swap.printInfo();
    swap.run();
    printf("After Swap, ");
    swap.printInfo();
    return 0;
}
