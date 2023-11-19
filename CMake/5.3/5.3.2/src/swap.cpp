#include "swap.h"
#include <iostream>

Swap::Swap(int a, int b)
{
    this->_a = a;
    this->_b = b;
}

Swap::~Swap()
{
}

void Swap::run()
{
    // 交换_a和_b的值
    int t = this->_a;
    this->_a = this->_b;
    this->_b = t;
}

void Swap::printInfo()
{
    printf("a = %d, b = %d\n", this->_a, this->_b);
}
