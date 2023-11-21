#include <iostream>
#include "gun.h"
#include "soldier.h"

int main()
{
    printf("this is a test string...\n");
    Soldier xsd("许三多", new Gun("AK47", 100));
    xsd.fire(30);
    xsd.load(100);
    printf("此时还有%d枚子弹\n", xsd.getGun()->getCartridgeNum());
    return 0;
}