#pragma once

class Swap
{
private:
    int _a;
    int _b;

public:
    Swap(int a, int b); // 构造函数
    ~Swap();            // 析构函数
    void run();         // 运行交换
    void printInfo();   // 打印信息
};