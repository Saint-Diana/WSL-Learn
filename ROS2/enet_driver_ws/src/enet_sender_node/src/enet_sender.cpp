// Client
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/serialization.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <enet/enet.h>
#include <vector>
#include <pthread.h>

void *msg_loop(void *arg)
{
    ENetHost *client = static_cast<ENetHost *>(arg);
    while (true)
    {
        ENetEvent event;
        while (enet_host_service(client, &event, 0) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_RECEIVE:
                printf("A packet of length %u containing %s was received from %x:%u on channel %u.\n",
                       event.packet->dataLength,
                       event.packet->data,
                       event.peer->address.host,
                       event.peer->address.port,
                       event.channelID);
                enet_packet_destroy(event.packet);
                break;

            default:
                break;
            }
        }
    }
    return nullptr;
}

class EnetSender : public rclcpp::Node
{
public:
    EnetSender()
        : Node("enet_sender_node")
    {
        sub_topic_name_ = this->declare_parameter("sub_topic_name", "/livox/lidar");
        server_ip_ = this->declare_parameter("server_ip", "127.0.0.1");
        server_port_ = this->declare_parameter("server_port", 6666);

        // initialize ENet
        if (enet_initialize())
        {
            RCLCPP_FATAL(this->get_logger(), "Failed to initialize ENet.");
            rclcpp::shutdown();
        }

        // create ENet client
        client_ = enet_host_create(nullptr, 1, 1, 0, 0);
        if (client_ == nullptr)
        {
            RCLCPP_FATAL(this->get_logger(), "Failed to create ENet client.");
            rclcpp::shutdown();
        }

        // set address
        enet_address_set_host(&address_, server_ip_.c_str());
        address_.port = server_port_;

        // connect to server
        peer_ = enet_host_connect(client_, &address_, 1, 0);
        if (peer_ == nullptr)
        {
            RCLCPP_FATAL(this->get_logger(), "Failed to connect to server.");
            rclcpp::shutdown();
        }

        if (enet_host_service(client_, &event_, 5000) > 0 &&
            event_.type == ENET_EVENT_TYPE_CONNECT)
        {
            RCLCPP_INFO(this->get_logger(), "Succeeded to connect to %s:%d",
                        server_ip_.c_str(), server_port_);
        }
        else
        {
            enet_peer_reset(peer_);
            RCLCPP_INFO(this->get_logger(), "Failed to connect to %s:%d",
                        server_ip_.c_str(), server_port_);
            rclcpp::shutdown();
        }

        pthread_create(&thread_, nullptr, msg_loop, client_);

        // create subscription
        sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            sub_topic_name_, 10,
            std::bind(&EnetSender::lidar_callback, this, std::placeholders::_1));
    }

    ~EnetSender()
    {
        pthread_join(thread_, nullptr);

        // disconnect
        enet_peer_disconnect(peer_, 0);
        while (enet_host_service(client_, &event_, 3000) > 0)
        {
            switch (event_.type)
            {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event_.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                RCLCPP_INFO(this->get_logger(), "Succeeded to disconnect from %s:%d",
                            server_ip_.c_str(), server_port_);
                break;

            default:
                break;
            }
        }

        enet_deinitialize();
    }

private:
    void lidar_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        rclcpp::SerializedMessage serialized_msg = msg_serialize(*msg);
        send_packet(peer_,
                    serialized_msg.get_rcl_serialized_message().buffer,
                    serialized_msg.get_rcl_serialized_message().buffer_length);
    }

    void send_packet(ENetPeer *peer, uint8_t *data, size_t length)
    {
        ENetPacket *packet = enet_packet_create(data, length, ENET_PACKET_FLAG_RELIABLE);
        if (!packet)
        {
            RCLCPP_FATAL(this->get_logger(), "Failed to create packet.");
            rclcpp::shutdown();
        }
        if (enet_peer_send(peer_, 0, packet) < 0)
        {
            RCLCPP_FATAL(this->get_logger(), "Failed to send.");
            rclcpp::shutdown();
        }
    }

    rclcpp::SerializedMessage msg_serialize(sensor_msgs::msg::PointCloud2 msg)
    {
        rclcpp::Serialization<sensor_msgs::msg::PointCloud2> serializer;
        rclcpp::SerializedMessage serialized_msg;
        serializer.serialize_message(&msg, &serialized_msg);

        return serialized_msg;
    }

    std::string sub_topic_name_;
    std::string server_ip_;
    int server_port_;
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_;
    ENetHost *client_;
    ENetAddress address_;
    ENetEvent event_;
    ENetPeer *peer_;
    pthread_t thread_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<EnetSender>());
    rclcpp::shutdown();
    return 0;
}