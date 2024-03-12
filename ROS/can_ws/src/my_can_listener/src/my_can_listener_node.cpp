#include <ros/ros.h>
#include <can_msgs/Frame.h>
#include <socketcan_interface/socketcan.h>
#include <socketcan_interface/threading.h>

class CANBusListener : public socketcan::Thread
{
public:
    CANBusListener(const std::string &can_interface) : nh_("~"), can_interface_(can_interface)
    {
        // 初始化CAN接收器
        if (!can_driver_.init(can_interface_, socketcan::Receiver))
        {
            ROS_ERROR("Failed to initialize CAN driver for interface: %s", can_interface_.c_str());
            return;
        }
        // 开始接收线程
        start();
    }

    ~CANBusListener()
    {
        // 停止接收线程
        stop();
        // 关闭CAN接收器
        can_driver_.shutdown();
    }

protected:
    void run() override
    {
        can_msgs::Frame frame;
        while (isRunning())
        {
            // 读取CAN报文
            if (can_driver_.receive(frame))
            {
                // 发布到ROS话题
                pub_.publish(frame);
            }
        }
    }

private:
    ros::NodeHandle nh_;
    ros::Publisher pub_ = nh_.advertise<can_msgs::Frame>("can_messages", 1000);
    std::string can_interface_;
    socketcan::SocketCANInterface can_driver_;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "can_bus_listener_node");
    if (argc != 2)
    {
        ROS_ERROR("Usage: can_bus_listener_node <can_interface>");
        return 1;
    }
    CANBusListener listener(argv[1]);
    ros::spin();
    return 0;
}