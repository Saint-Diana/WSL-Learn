#include "ros/ros.h"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "param_get");
    ros::NodeHandle nh;
    // 方案1：nh
    std::string type = nh.param<std::string>("type", "Unknown");
    double radius = nh.param("radius", 0.5);
    // bool result = nh.getParam("radius", radius);
    ROS_INFO("查询参数服务器，获取参数：type = %s, radius = %.2f", type.c_str(), radius);

    // 方案2：ros::param
    double radius_param = 0.0;
    bool isSuccessful = ros::param::get("radius_param", radius_param);
    if (isSuccessful)
    {
        ROS_INFO("查询参数服务器，获取参数：radius_param = %.2f", radius_param);
    }
    else
    {
        ROS_ERROR("查询的变量不存在");
        return 1;
    }

    // getParamCached 与 getParam类似，只是性能上有提升

    // getParamNames
    std::vector<std::string> keys;
    nh.getParamNames(keys);
    for (auto &&key : keys)
    {
        ROS_INFO("遍历到的元素：%s", key.c_str());
    }

    // hasParam() 返回True表示存在，False表示不存在
    bool flag1 = nh.hasParam("radius");
    bool flag2 = nh.hasParam("radiusxxx");
    ROS_INFO("radius 存在吗？ %d", flag1);
    ROS_INFO("radiusxxx 存在吗？ %d", flag2);

    return 0;
}