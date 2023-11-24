#include "ros/ros.h"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "demo_param_del");
    ros::NodeHandle nh;
    bool result = nh.deleteParam("haha");
    ROS_INFO("删除结果：%d", result);
    return 0;
}