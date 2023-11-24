#include "ros/ros.h"
#include "demo_server_client/add.h"

bool doReq(demo_server_client::add::Request &req,
           demo_server_client::add::Response &resp)
{
    int num1 = req.num1;
    int num2 = req.num2;

    ROS_INFO("服务器接收到的数据为：num1 = %d, num2 = %d", num1, num2);

    // 逻辑处理
    if (num1 < 0 || num2 < 0)
    {
        ROS_ERROR("提交的数据异常:数据不可以为负数");
        return false;
    }

    // 如果没有异常，那么相加并将结果赋值给 resp
    resp.sum = num1 + num2;
    return true;
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "server");

    ros::NodeHandle nh;

    // 创建服务对象
    ros::ServiceServer server = nh.advertiseService("add", doReq);

    ROS_INFO("服务启动...");

    ros::spin();
    return 0;
}