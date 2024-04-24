// Server
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/serialization.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <enet/enet.h>

class EnetReceiver : public rclcpp::Node
{
public:
    EnetReceiver()
        : Node("enet_receiver_node")
    {
        pub_topic_name_ = this->declare_parameter("pub_topic_name", "/lidar");
        server_port_ = this->declare_parameter("server_port", 6666);

        // initialize ENet
        if (enet_initialize() != 0)
        {
            RCLCPP_FATAL(this->get_logger(), "Failed to initialize ENet.");
            rclcpp::shutdown();
        }

        // set address
        address_.host = ENET_HOST_ANY;
        address_.port = server_port_;

        // create ENet server
        server_ = enet_host_create(&address_, 32, 1, 0, 0);
        if (server_ == nullptr)
        {
            RCLCPP_FATAL(this->get_logger(), "Failed to create ENet server.");
            rclcpp::shutdown();
        }

        pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(
            pub_topic_name_, 10);
    }

    ~EnetReceiver()
    {
        if (server_ != nullptr)
        {
            enet_host_destroy(server_);
        }
        enet_deinitialize();
    }

    void receive_and_publish()
    {
        while (enet_host_service(server_, &event_, 1000) > 0)
        {
            switch (event_.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
            {
                RCLCPP_INFO(this->get_logger(), "A new client %x:%u connected to this server.\n",
                            event_.peer->address.host,
                            event_.peer->address.port);
                break;
            }

            case ENET_EVENT_TYPE_RECEIVE:
            {
                RCLCPP_INFO(this->get_logger(), "A packet of length %u containing %s was received from %x:%u on channel %u.\n",
                            event_.packet->dataLength,
                            event_.packet->data,
                            event_.peer->address.host,
                            event_.peer->address.port,
                            event_.channelID);
                auto deserialized_msg = msg_desrialize(event_);
                pub_->publish(deserialized_msg);
                enet_packet_destroy(event_.packet);
                break;
            }

            default:
                break;
            }
        }
    }

private:
    sensor_msgs::msg::PointCloud2 msg_desrialize(ENetEvent event)
    {
        rclcpp::SerializedMessage serialized_msg(event.packet->dataLength);
        memcpy(serialized_msg.get_rcl_serialized_message().buffer,
               event.packet->data, event.packet->dataLength);
        serialized_msg.get_rcl_serialized_message().buffer_length = event.packet->dataLength;
        rclcpp::Serialization<sensor_msgs::msg::PointCloud2> serializer;
        auto msg = sensor_msgs::msg::PointCloud2();
        serializer.deserialize_message(&serialized_msg, &msg);
        return msg;
    }

    std::string pub_topic_name_;
    int server_port_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_;
    ENetHost *server_;
    ENetAddress address_;
    ENetEvent event_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<EnetReceiver>();
    while (rclcpp::ok())
    {
        node->receive_and_publish();
    }
    rclcpp::shutdown();
    return 0;
}