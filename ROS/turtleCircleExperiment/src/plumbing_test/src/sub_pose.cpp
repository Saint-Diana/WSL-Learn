#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

void doMsg(const turtlesim::Pose::ConstPtr &pose)
{
    ROS_INFO("x = %.2f\ny = %.2f\ntheta = %.2f\nlinear_velocity = %.2f\nangular_velocity = %.2f\n==========", pose->x, pose->y, pose->theta, pose->linear_velocity, pose->angular_velocity);
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "sub_twist");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>("/turtle1/pose", 20, doMsg);
    ros::spin();
    return 0;
}