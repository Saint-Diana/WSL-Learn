#include "ros/ros.h"

/*
    需要实现参数的新增和修改
    需求：
        首先设置机器人的共享参数：类型、半径(0.15m)
        再修改半径(0.2m)

    实现：
        ros::NodeHandle
            setParam()
        ros::param
            set()
*/

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");

    // 初始化 ros 节点
    ros::init(argc, argv, "set_param");

    // 创建 ros 节点句柄
    ros::NodeHandle nh;

    // 参数增
    // 方案1：nh
    nh.setParam("type", "car");
    nh.setParam("radius", 0.15);

    // 方案2：ros::param
    ros::param::set("type_param", "car");
    ros::param::set("radius_param", "0.15");

    // 参数改
    // 方案1：nh
    nh.setParam("radius", 0.2);

    // 方案2：ros::param
    ros::param::set("radius_param", 0.2);

    return 0;
}