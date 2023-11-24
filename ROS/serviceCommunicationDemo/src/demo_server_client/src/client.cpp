#include "ros/ros.h"
#include "demo_server_client/add.h"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");

    // 调用时动态传值,如果通过 launch 的 args 传参，需要传递的参数个数 +3
    if (argc != 3)
    // if (argc != 5)//launch 传参(0-文件路径 1传入的参数 2传入的参数 3节点名称 4日志路径)
    {
        ROS_ERROR("请提交两个整数");
        return 1;
    }

    ros::init(argc, argv, "client");

    ros::NodeHandle nh;

    // 创建客户端对象
    ros::ServiceClient client = nh.serviceClient<demo_server_client::add>("add");

    // 等待服务启动成功
    // 方式1
    ros::service::waitForService("add");
    // 方式2
    //  client.waitForExistence();

    // 组织请求数据
    demo_server_client::add add;
    add.request.num1 = atoi(argv[1]);
    add.request.num2 = atoi(argv[2]);

    // 发送请求
    bool isSuccessful = client.call(add);
    if (!isSuccessful)
    {
        ROS_ERROR("请求处理失败...");
        return 1;
    }
    else
    {
        ROS_INFO("请求处理成功，响应结果：sum = %d", add.response.sum);
    }

    return 0;
}