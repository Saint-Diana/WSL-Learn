#include <ros/ros.h>
#include <can_msgs/Frame.h>

void canMessageReceived(const can_msgs::Frame::ConstPtr &msg)
{
    ROS_INFO_STREAM("接收到CAN报文: ID=" << msg->id << " DLC=" << (int)msg->dlc << " data=");
    // 处理CAN报文数据...
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "can_listener");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe<can_msgs::Frame>("can_topic", 1000, canMessageReceived);

    ros::spin();

    return 0;
}