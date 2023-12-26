#include "ros/ros.h"

void cb(const ros::TimerEvent &event)
{
    ROS_INFO("-------");
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "demo03_time", ros::init_options::AnonymousName);
    // 调研时间api必须创建 NodeHandle
    ros::NodeHandle nh;

    // 参考系：1970-01-01 00:00:00
    // 获取当前时刻
    ros::Time currentTime = ros::Time::now();
    ROS_INFO("当前时刻：%.2f", currentTime.toSec());
    ROS_INFO("当前时刻：%d", currentTime.sec);

    // 设置指定时刻
    ros::Time t1(20, 12345678);
    ros::Time t2(100.35);

    // 持续时间
    ros::Duration d(4.5); // 单位为 秒
    d.sleep();            // 休眠4.5s

    // 时间运算
    // 获取开始执行的时刻
    ros::Time begin = ros::Time::now();
    // 模拟运行时间
    ros::Duration runTime(5);
    // 计算结束时刻 = 开始 + 持续时间
    ros::Time end = begin + runTime;
    ROS_INFO("开始时刻：%.2f", begin.toSec());
    ROS_INFO("结束时刻：%.2f", end.toSec());

    // 注意： 时刻与时刻不可以相加！但是可以相减，但是产生的是ros::Duration对象。
    ros::Duration sepration = end - begin;

    // 持续时间和持续时间运算
    ros::Duration d1 = d + runTime;
    ros::Duration d2 = d - runTime;
    ROS_INFO("d1：%.2f", d1.toSec());
    ROS_INFO("d2：%.2f", d2.toSec());

    // 定时器
    // 每隔 1s，在控制台输出一段文本S

    // 策略1：使用ros::Rate对象
    // ros::Rate r(1);
    // while (ros::ok())
    // {
    //     ROS_INFO("当前时刻：%.10f", ros::Time::now().toSec());
    //     ros::spinOnce();
    //     r.sleep();
    // }

    // 策略2：使用ros::Timer
    /*
        ros::Timer createTimer(ros::Duration period,  // 时间间隔
            const ros::TimerCallback &callback,       // 回调函数
            bool oneshot = false,                     // 是否是一次性
            bool autostart = true) const              // 自动启动

    */

    ros::Timer timer = nh.createTimer(ros::Duration(1), cb);
    // timer.start(); // 手动启动
    ros::spin(); // 需要回旋调用回调函数

    return 0;
}