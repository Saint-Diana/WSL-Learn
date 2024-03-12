/**
 * @file can_publisher.cpp
 * @author your name (you@domain.com)
 * @brief This node is aimed at getting CAN messages from CAN Interface(e.g. vcan0),
 *        then publish them to the topic "can_topic".
 * @version 0.1
 * @date 2024-03-12
 *
 * @copyright Copyright (c) 2024
 */
#include "rclcpp/rclcpp.hpp"
#include "can_msgs/msg/frame.hpp"
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

class CANPublisher: public rclcpp::Node
{
public:
    CANPublisher(): Node("can_publisher")
    {
        publisher_ = this->create_publisher<can_msgs::msg::Frame>("can_topic", 10);
        open_socket();
        read_and_publish();
    }
private:
    void open_socket()
    {
        struct sockaddr_can addr;
        struct ifreq ifr;

        // create the socket
        socket_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);
        if (socket_ < 0)
        {
            RCLCPP_FATAL(this->get_logger(), "Failed to open the socket");
            rclcpp::shutdown();
        }

        // bind the CAN Interface
        strcpy(ifr.ifr_name, "vcan0");
        ioctl(socket_, SIOCGIFINDEX, &ifr);

        addr.can_family = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;

        // bind the socket
        bind(socket_, (struct sockaddr *)&addr, sizeof(addr));
    }

    void read_and_publish()
    {
        struct can_frame frame;
        while (rclcpp::ok())
        {
            // read CAN Frames
            int nbytes = read(socket_, &frame, sizeof(struct can_frame));

            if (nbytes < 0)
            {
                RCLCPP_ERROR(this->get_logger(), "Failed to read CAN Frames.");
                continue;
            }

            RCLCPP_INFO(this->get_logger(), "Getting CAN Frame: id=0x%08x", frame.can_id);

            if ((size_t)nbytes == sizeof(struct can_frame))
            {
                // transfer CAN Frames to ROS topic, then publish them.
                auto message = can_msgs::msg::Frame();
                message.id = frame.can_id;
                message.dlc = frame.can_dlc;
                std::copy(std::begin(frame.data), std::end(frame.data), std::begin(message.data));
                publisher_->publish(message);
            }
        }
    }

    int socket_;
    rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr publisher_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CANPublisher>());
    rclcpp::shutdown();
    return 0;
}