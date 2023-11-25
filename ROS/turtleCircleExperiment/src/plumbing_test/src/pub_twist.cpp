// 1.包含头文件
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

/*
    需求：发布运动信息
        话题：/turtle1/cmd_vel
        消息：geometry_msgs/Twist

    1.包含头文件
    2.初始化 ros node
    3.创建 node handle
    4.创建 publisher
    5.发布逻辑实现
    6.spinOnce()
*/

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    // 2.初始化 ros node
    ros::init(argc, argv, "pub_twist");

    // 3.创建 node handle
    ros::NodeHandle nh;

    // 4.创建 publisher
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 20);

    double speed = 5.0;
    ros::Rate r(10);
    // 5.发布逻辑实现
    while (ros::ok())
    {
        geometry_msgs::Twist twist;
        twist.linear.x = speed;
        twist.angular.z = speed;
        pub.publish(twist);

        r.sleep();

        // 6.spinOnce()
        ros::spinOnce();
    }

    return 0;
}