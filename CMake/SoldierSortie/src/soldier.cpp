#include "soldier.h"

Soldier::Soldier()
{
    this->name = "unknown";
    this->gun = nullptr;
}

Soldier::Soldier(std::string name, Gun *gun)
{
    this->name = name;
    this->gun = new Gun(gun->getName(), gun->getCartridgeNum());
}

Soldier::~Soldier()
{
    this->name = "unknown";
    delete this->gun;
}

void Soldier::fire(int num)
{
    // 调用gun的emit函数
    this->gun->emit(num);
}

void Soldier::load(int num)
{
    // 调用gun的load方法
    this->gun->load(num);
}

std::string Soldier::getName()
{
    return this->name;
}

void Soldier::setName(std::string name)
{
    this->name = name;
}

Gun *Soldier::getGun()
{
    return this->gun;
}

void Soldier::setGun(Gun *gun)
{
    this->gun = new Gun(gun->getName(), gun->getCartridgeNum());
}
