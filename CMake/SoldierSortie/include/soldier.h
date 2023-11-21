#pragma once
#include <string>
#include "gun.h"

class Soldier
{
private:
    /**
     * 姓名
     */
    std::string name;
    /**
     * 枪
     */
    Gun *gun;

public:
    Soldier();
    Soldier(std::string name, Gun *gun);
    ~Soldier();
    /**
     * 开火
     */
    void fire(int num);
    /**
     * 装填子弹
     */
    void load(int num);

    /* getter & setter*/
    std::string getName();
    void setName(std::string name);
    Gun *getGun();
    void setGun(Gun *gun);
};