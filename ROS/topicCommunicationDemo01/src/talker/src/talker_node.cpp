#include "talker_node.h"
// 1.包含头文件
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char *argv[])
{
    // 设置编码，防止中文乱码
    setlocale(LC_ALL, "");

    // 2.初始化 ROS 节点，取名为 talker_node
    ros::init(argc, argv, "talker_node");

    // 3.实例化 ROS 句柄
    ros::NodeHandle nh; // 该类封装了 ROS 中的一些常用功能

    // 4.实例化 发布者 对象
    // 泛型：发布的消息类型
    // 参数1：要发布到的话题
    // 参数2：队列中最大保存的消息数量，超过此阈值时，按照FIFO规则进行抛弃
    ros::Publisher pub = nh.advertise<std_msgs::String>("chatter", 20);

    // 5.组织被发布的数据，并且编写逻辑来发布数据
    // 数据(动态组织)
    std_msgs::String msg;
    std::string msg_front = "你好！"; // 消息前缀
    int count = 0; // 消息计数器

    // 逻辑(一秒1次)
    ros::Rate r(1);

    // 延迟第一条消息的发送
    ros::Duration(3.0).sleep();

    // 节点不死
    while(ros::ok())
    {
        // 使用 stringstream 拼接字符串并编号
        std::stringstream ss;
        ss << msg_front << count;
        msg.data = ss.str();

        // 发布消息
        pub.publish(msg);

        // 加入调试，打印发送的消息
        ROS_INFO("发送的消息：%s", msg.data.c_str());

        // 按照前面制定的发布频率自动休眠   休眠时间 = 1 / 频率
        r.sleep();

        count++; // 循环结束前，消息计数器自增

        ros::spinOnce(); // 暂无应用
    }
    return 0;
}