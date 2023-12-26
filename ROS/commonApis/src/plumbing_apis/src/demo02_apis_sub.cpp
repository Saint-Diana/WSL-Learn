#include "ros/ros.h"
#include "std_msgs/String.h"

void doMsg(const std_msgs::String::ConstPtr &msg)
{
    ROS_INFO("接收的数据是：%s", msg->data.c_str());
}

int main(int agrc, char **argv)
{
    setlocale(LC_ALL, "");
    ros::init(agrc, argv, "demo02_apis_sub", ros::init_options::AnonymousName);
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<std_msgs::String>("/fang", 10, doMsg);
    ros::spin();
    return 0;
}