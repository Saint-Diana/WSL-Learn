#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    /*
        初始化 ROS 节点

        参数：
            1. argc         —— 封装实参个数(n + 1)
            2. argv         —— 封装实参数组
            3. name         —— 为节点命名(唯一性)
            4. options      —— 节点启动选项

        返回值： void

        使用：
            1. argc 与 argv 的使用
                如果按照 ROS 中的特定格式(rosrun xxx xxx arg1 agr2 ...)传入实参，
                那么 ROS 可以加以使用。比如用来设置全局参数，给节点重命名等。

            2. options 的使用
                节点名称需要保证唯一，会导致一个问题：同一个节点不能重复启动。
                结果： ROS 中当有重名的节点启动时，之前的节点会被关闭。

                需求：特定场景下，需要同一个节点多次启动且都能正常运行，怎么办？
                解决方法：在 options 参数使用ros::init_options::AnonymousName
                    当创建 ROS 节点时，会在用户自定义的节点名称后面加上随机数，从而避免重名问题。
    */
    ros::init(argc, argv, "demo01_apis_pub", ros::init_options::AnonymousName);

    ros::NodeHandle nh;

    /*
        作用：创建发布者对象

        模板：被发布消息的类型

        参数：
            1. topic            —— 话题名称
            2. queue_size       —— 队列长度
            3. latch            —— bool，如果设置为 true，那么会保存发布方的最后一条消息
                                   并且新的订阅方连接到发布方时，发布方会将保存的最后一条消息发送给订阅方

        使用：
            latch 设置为 true 的作用？
                以静态地图发布为例
                方案1：可以使用固定频率发送地图数据，但是效率低下；
                方案2：可以将地图发布对象的 latch 设置为 true，并且发布方只发送一次数据，每当订阅方连接时，将地图数据发送给订阅方(只发送一次)，效率高。
    */
    ros::Publisher pub = nh.advertise<std_msgs::String>("/fang", 10, true);

    int cnt = 0;
    ros::Rate r(10);
    std_msgs::String msg;
    while (ros::ok())
    {
        cnt++;
        std::stringstream ss;
        ss << "hello ---> " << cnt;
        msg.data = ss.str();
        if (cnt <= 10)
        {
            pub.publish(msg);
            ROS_INFO("发布的数据是：%s", msg.data.c_str());
        }
        r.sleep();
        ros::spinOnce();
    }
    return 0;
}