#include "ros/ros.h"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    std::map<std::string, std::string> map;
    map["__ns"] = "namespace";
    ros::init(map, "name");
    ros::NodeHandle nh;
    ros::Rate r(1);
    while (ros::ok())
    {
        ROS_INFO("...");
        r.sleep();
        ros::spinOnce();
    }
    return 0;
}