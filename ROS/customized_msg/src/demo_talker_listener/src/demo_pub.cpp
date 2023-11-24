// 1.包含头文件
#include "ros/ros.h"
#include "demo_talker_listener/Person.h"

int main(int argc, char **argv)
{
    // 2.设置编码格式，防止中文乱码
    setlocale(LC_ALL, "");

    // 3.初始化ros
    ros::init(argc, argv, "demo_pub");

    // 4.创建 ros节点线程
    ros::NodeHandle nh;

    // 5.使用 NodeHandle 对象创建Publisher
    ros::Publisher pub = nh.advertise<demo_talker_listener::Person>("chat", 10);

    // 6.创建 ros::Rate 对象设置向 topic 发送消息的频率(HZ)
    ros::Rate r(3); // 3HZ == 3 times / s

    int cnt = 0;

    // 7.只要 node 还存在，就持续发
    while (ros::ok())
    {
        // 8.创建消息
        demo_talker_listener::Person person;
        person.name = "Shenhuichang";
        person.age = 21;
        person.height = 171;
        
        // 9.发送消息
        pub.publish(person);

        // 10.打印日志
        ROS_INFO("发送的第%d条消息的内容为\n姓名：%s\n年龄：%d\n身高：%.2f", cnt, person.name.c_str(), person.age, person.height);

        cnt++;
        r.sleep();

        ros::spinOnce();
    }

    return 0;
}
