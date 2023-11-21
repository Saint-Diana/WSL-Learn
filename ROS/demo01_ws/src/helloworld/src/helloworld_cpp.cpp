// 1，包含ROS的头文件
#include "ros/ros.h"

int main(int argc, char *argv[])
{
    // 2.初始化ROS节点(node)
    ros::init(argc, argv, "hello_node"); // 节点名称为 hello_node
    // 3.输出日志
    ROS_INFO("hello world");
}

/*
    编写ROS项目的步骤：
    1、创建工作空间。创建一个文件夹作为工作空间，在下面创建一个src文件夹作为功能包代码存放位置。
        然后在工作空间下执行catkin_make命令进行编译。
    2、在src目录下创建功能包。使用catkin_create_pkg 包名 roscpp rospy std_msgs命令进行。
    3、在创建好的功能包下写代码。include文件夹下面写头文件，src文件夹下面写源代码。
    4、编写好代码后，修改功能包下的CMakeLists.txt用于编译链接生成可执行文件。需要修改其中的add_executable和target_link_libraries。
    5、回到工作空间下使用catkin_make进行编译。

    执行ROS项目的步骤：
    1、首先启动ROS核心。使用roscore命令即可。
    2、把当前工作空间的启动命令添加到当前用户的bash当中。使用命令source ./devel/setup.bash。
    3、使用rosrun 功能包名 可执行文件名 这条命令来执行相应的可执行文件。
*/