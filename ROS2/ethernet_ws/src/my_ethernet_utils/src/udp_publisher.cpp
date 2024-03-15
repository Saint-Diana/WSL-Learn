#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <rclcpp/rclcpp.hpp>
#include <udp_msgs/msg/udp_packet.hpp>
#include <asio.hpp>

class UDPPublisher: public rclcpp::Node
{
public:
    UDPPublisher()
    : Node("udp_publisher"),
      io_service_(),
      socket_(io_service_)
    {
        // declare parameters
        this->declare_parameter("topic_name", "ethernet_message");
        this->declare_parameter("ip", "0.0.0.0");
        this->declare_parameter("port", 12345);

        // get parameters
        this->get_parameter("topic_name", topic_name_);
        this->get_parameter("ip", ip_);
        this->get_parameter("port", port_);

        RCLCPP_INFO(this->get_logger(), "ip: %s, port: %d", ip_.c_str(), port_);

        // initialize publisher
        publisher_ = this->create_publisher<udp_msgs::msg::UdpPacket>(topic_name_, 10);
        // set the ip address and port which are listened by the PC
        asio::ip::udp::endpoint listen_endpoint(asio::ip::address::from_string(ip_), port_);
        // open socket, bind it to the provided ip address and port
        socket_.open(asio::ip::udp::v4());
        socket_.bind(listen_endpoint);
        // start receive
        start_receive();
    }

private:
    void start_receive()
    {
        RCLCPP_INFO(this->get_logger(), "START RECEIVE");

        RCLCPP_INFO(this->get_logger(), "Socket is opened: %d", socket_.is_open());

        // remote_endpoint_ will be initialized automatically
        socket_.async_receive_from(
            asio::buffer(recv_buffer_), remote_endpoint_,
            std::bind(&UDPPublisher::handle_receive, this,
                        std::placeholders::_1, std::placeholders::_2)
        );
    }

    void handle_receive(const asio::error_code& error, std::size_t bytes_transferred)
    {
        if (!error || error == asio::error::message_size)
        {
            RCLCPP_INFO(this->get_logger(), "RECEIVE ONE UDP PACKET");

            auto message = std::make_shared<udp_msgs::msg::UdpPacket>();
            message->data = std::vector<uint8_t>(recv_buffer_.begin(),
                                                    recv_buffer_.begin() + bytes_transferred);
            // publish the message
            publisher_->publish(*message);

            // cotinue to receive
            start_receive();
        }
    }

    std::string ip_;             // ip of the PC
    int port_;                   // port of UDP packets in the PC
    std::string topic_name_;     // name of published ROS2 topic
    asio::io_service io_service_;
    asio::ip::udp::socket socket_;
    asio::ip::udp::endpoint remote_endpoint_;
    std::array<uint8_t, 65536> recv_buffer_;
    rclcpp::Publisher<udp_msgs::msg::UdpPacket>::SharedPtr publisher_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<UDPPublisher>());
    rclcpp::shutdown();
    return 0;
}


