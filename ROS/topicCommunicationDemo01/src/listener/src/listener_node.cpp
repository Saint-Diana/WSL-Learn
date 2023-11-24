#include "listener_node.h"
// 1.包含头文件
#include "ros/ros.h"
#include "std_msgs/String.h"

void doMessage(const std_msgs::String::ConstPtr& msg_p)
{
    ROS_INFO("我听见：%s", msg_p->data.c_str());
}


int main(int argc, char *argv[])
{
    // 设置编码，防止中文乱码
    setlocale(LC_ALL, "");
    
    // 2.初始化 ROS 节点，取名为 listener_node
    ros::init(argc, argv, "listener_node");

    // 3.实例化 ROS 句柄
    ros::NodeHandle nh;

    // 4.实例化 订阅者 对象
    // 参数3：当接收到发布者的消息时触发的函数(回调函数)
    ros::Subscriber sub = nh.subscribe<std_msgs::String>("chatter", 20, doMessage);

    // 5.设置循环调用回调函数
    ros::spin(); // 循环读取接收的数据，并调用回调函数处理

    return 0;
}