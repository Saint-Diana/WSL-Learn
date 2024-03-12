/**
 * @file can_recorder.cpp
 * @author your name (you@domain.com)
 * @brief This node is aimed at recording CAN messages through subscribing the ROS topic -- "can_topic".
 * @version 0.1
 * @date 2024-03-12
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "can_msgs/msg/frame.hpp"

class CANRecorder: public rclcpp::Node
{
public:
    CANRecorder(): Node("can_recorder")
    {
        subscription_ = this->create_subscription<can_msgs::msg::Frame>(
            "can_topic", // the name of can topic
            10,
            std::bind(&CANRecorder::topic_callback, this, std::placeholders::_1)
        );
    }

private:
    void topic_callback(const can_msgs::msg::Frame::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), "Recording CAN Frame: id=0x%08x", msg->id);
        // TODO: add codes to store can message to a bag file.
    }
    rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr subscription_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CANRecorder>());
    rclcpp::shutdown();
    return 0;
}