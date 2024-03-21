#include "rclcpp/rclcpp.hpp"
#include "rclcpp/serialization.hpp"
#include "rosbag2_cpp/reader.hpp"
#include "rosbag2_storage/serialized_bag_message.hpp"
#include "can_msgs/msg/frame.hpp"
#include "udp_msgs/msg/udp_packet.hpp"
#include "yaml-cpp/yaml.h"
#include <memory>
#include <variant>

using PublisherVariant = std::variant<
    rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr,
    rclcpp::Publisher<udp_msgs::msg::UdpPacket>::SharedPtr>;

using namespace std::chrono_literals;

class TopicPlayer : public rclcpp::Node
{
public:
    TopicPlayer() : Node("topic_player")
    {
        // get parameters
        bag_file_path_ = this->declare_parameter("bag_file_path", "my_bag");

        reader_ = std::make_unique<rosbag2_cpp::Reader>();
        reader_->open(bag_file_path_);

        // get metadata
        auto metadata = reader_->get_all_topics_and_types();
        for (const auto &topic : metadata)
        {
            topics_name_to_type[topic.name] = topic.type;
        }

        for (const auto &topic : metadata)
        {
            // create publisher
            std::string topic_type = topics_name_to_type.find(topic.name)->second;
            if (topic_type == "can_msgs/msg/Frame")
            {
                auto publisher = this->create_publisher<can_msgs::msg::Frame>(topic.name, 10);
                publishers_[topic.name] = publisher;
            }
            else if (topic_type == "udp_msgs/msg/UdpPacket")
            {
                auto publisher = this->create_publisher<udp_msgs::msg::UdpPacket>(topic.name, 10);
                publishers_[topic.name] = publisher;
            }
        }

        timer_ = create_wall_timer(10ms, std::bind(&TopicPlayer::timer_callback, this)); // in this place, `10ms` is time of cycle of publishing topics
    }

private:
    void timer_callback()
    {
        RCLCPP_INFO(this->get_logger(), "Start playing");
        if (reader_->has_next())
        {
            auto msg = reader_->read_next();
            rclcpp::SerializedMessage serialized_msg(*msg->serialized_data);
            std::string topic_name = msg->topic_name;
            std::string topic_type = topics_name_to_type.find(topic_name)->second;

            RCLCPP_INFO(this->get_logger(), "topic_name: %s, topic_type: %s", topic_name.c_str(), topic_type.c_str());

            if (topic_type == "can_msgs/msg/Frame")
            {
                auto ros_msg = std::make_shared<can_msgs::msg::Frame>();
                can_serialization_.deserialize_message(&serialized_msg, ros_msg.get());
                auto publisher = std::get<rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr>(publishers_.find(topic_name)->second);
                publisher->publish(*ros_msg);
            }
            else if (topic_type == "udp_msgs/msg/Frame")
            {
                auto ros_msg = std::make_shared<udp_msgs::msg::UdpPacket>();
                can_serialization_.deserialize_message(&serialized_msg, ros_msg.get());
                auto publisher = std::get<rclcpp::Publisher<udp_msgs::msg::UdpPacket>::SharedPtr>(publishers_.find(topic_name)->second);
                publisher->publish(*ros_msg);
            }
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "No more messages to publish, stopping timer.");
            timer_->cancel();   // 取消定时器
            rclcpp::shutdown(); // 关闭节点
        }
    }

    std::string bag_file_path_; // path of storage folder
    std::map<std::string, std::string> topics_name_to_type;
    std::unordered_map<std::string, PublisherVariant> publishers_;
    rclcpp::Serialization<can_msgs::msg::Frame> can_serialization_;
    rclcpp::Serialization<udp_msgs::msg::UdpPacket> udp_serialization_;
    std::unique_ptr<rosbag2_cpp::Reader> reader_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TopicPlayer>());
    rclcpp::shutdown();
    return 0;
}