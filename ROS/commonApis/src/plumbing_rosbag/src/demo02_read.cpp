#include "ros/ros.h"
#include "rosbag/bag.h"
#include "std_msgs/String.h"
#include "rosbag/view.h"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "rosbag_read", ros::init_options::AnonymousName);
    ros::NodeHandle nh;

    // 创建 rosbag 对象
    rosbag::Bag bag;

    // 打开 .bag 文件
    bag.open("/home/shenhuichang/learn/ROS/commonApis/src/plumbing_rosbag/bags/test.bag", rosbag::BagMode::Read);

    // 读数据
    for (rosbag::MessageInstance const m : rosbag::View(bag))
    {
        std_msgs::String::ConstPtr p = m.instantiate<std_msgs::String>();
        if (p != nullptr)
        {
            ROS_INFO("读取的数据:%s", p->data.c_str());
        }
    }

    // 关闭文件流
    bag.close();

    return 0;
}