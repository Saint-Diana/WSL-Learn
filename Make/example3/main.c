#include <stdio.h>

/* 定义两个全局变量 */
int X = 30;
int Y = 20;

/* 函数会自动在所有源文件中进行搜索 */
int max();

int main()
{
    int result = max();
    printf("the max value is %d\n", result);
    return 0;
}