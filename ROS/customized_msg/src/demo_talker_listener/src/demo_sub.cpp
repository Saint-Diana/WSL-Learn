#include "ros/ros.h"
#include "demo_talker_listener/Person.h"

int cnt = 0;

void doMsg(const demo_talker_listener::Person::ConstPtr &person)
{
    ROS_INFO("接收的第%d条消息的内容为\n姓名：%s\n年龄：%d\n身高：%.2f", cnt, person->name.c_str(), person->age, person->height);
    cnt++;
}

int main(int argc, char **argv)
{   
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "demo_sub");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("chat", 10, doMsg);

    ros::spin();
    return 0;
}