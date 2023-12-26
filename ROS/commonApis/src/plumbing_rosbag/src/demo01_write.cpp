#include "ros/ros.h"
#include "rosbag/bag.h"
#include "std_msgs/String.h"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "rosbag_write", ros::init_options::AnonymousName);
    ros::NodeHandle nh;

    // 创建 rosbag 对象
    rosbag::Bag bag;

    // 打开文件流
    bag.open("/home/shenhuichang/learn/ROS/commonApis/src/plumbing_rosbag/bags/test.bag", rosbag::BagMode::Write);

    // 写入
    std_msgs::String msg;
    msg.data = "hello world";
    bag.write("/chatter", ros::Time::now(), msg);
    bag.write("/chatter", ros::Time::now(), msg);
    bag.write("/chatter", ros::Time::now(), msg);
    bag.write("/chatter", ros::Time::now(), msg);
    bag.write("/chatter", ros::Time::now(), msg);

    // 关闭 rosbag 对象
    bag.close();

    return 0;
}