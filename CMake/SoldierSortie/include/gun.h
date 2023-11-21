#pragma once
#include <string>

class Gun
{
private:
    /**
     * 名字
     */
    std::string name;
    /**
     * 子弹数量
     */
    int cartridgeNum;

public:
    Gun();
    Gun(std::string name, int num);
    ~Gun();
    /**
     * 发射子弹
     */
    void emit(int num);
    /**
     * 装填子弹
     */
    void load(int num);

    /* getter & setter*/
    std::string getName();
    void setName(std::string name);
    int getCartridgeNum();
    void setCartridgeNum(int num);
};