#include "ros/ros.h"
#include "plumbing_head/hello.h"

namespace hello_ns
{
    void MyHello::run()
    {
        ROS_INFO("run 函数执行 ......");
    }
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "hello", ros::init_options::AnonymousName);
    hello_ns::MyHello my;
    my.run();

    return 0;
}