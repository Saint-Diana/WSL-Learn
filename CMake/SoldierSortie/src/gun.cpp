#include "gun.h"

Gun::Gun()
{
    this->name = "unknown";
    this->cartridgeNum = 0;
}

Gun::Gun(std::string name, int num)
{
    this->name = name;
    this->cartridgeNum = num >= 0 ? num : 0;
}

Gun::~Gun()
{
}

void Gun::emit(int num)
{
    num = num >= 0 ? num : 0;
    if (this->cartridgeNum < num)
    {
        printf("子弹数量不足，请先装填%d枚子弹！\n", num - this->cartridgeNum);
        return;
    }
    else
    {
        this->cartridgeNum -= num;
        printf("发射子弹成功，现有%d枚子弹！\n", this->cartridgeNum);
    }
}

void Gun::load(int num)
{
    num = num >= 0 ? num : 0;
    this->cartridgeNum += num;
    printf("装填子弹成功，现有%d枚子弹！\n", this->cartridgeNum);
}

std::string Gun::getName()
{
    return this->name;
}

void Gun::setName(std::string name)
{
    this->name = name;
}

int Gun::getCartridgeNum()
{
    return this->cartridgeNum;
}

void Gun::setCartridgeNum(int num)
{
    this->cartridgeNum = num >= 0 ? num : 0;
}
