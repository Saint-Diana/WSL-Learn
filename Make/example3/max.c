#include <stdio.h>

/* 将main.c中定义的两个外部变量引入到当前源文件中*/
extern int X;
extern int Y;

int max()
{
    return (X > Y ? X : Y);
}