#include "rclcpp/rclcpp.hpp"
#include "rclcpp/serialization.hpp"
#include "rclcpp/serialized_message.hpp"
#include "rosbag2_cpp/writer.hpp"
#include "can_msgs/msg/frame.hpp"
#include "udp_msgs/msg/udp_packet.hpp"
#include "yaml-cpp/yaml.h"

class TopicRecorder : public rclcpp::Node
{
public:
  TopicRecorder() : Node("topic_recorder")
  {
    // declare parameters in the yaml file
    this->declare_parameter<std::string>("bag_file_path", "my_bag");

    // get parameters from the yaml file
    this->get_parameter("bag_file_path", bag_file_path_);

    // get configuration in the yaml file
    YAML::Node config = YAML::LoadFile("/home/shen/learn/ROS2/record_ws/src/my_record_utils/config/topics_config.yaml");
    YAML::Node topics = config["topics"];

    // initialize writer_
    writer_ = std::make_unique<rosbag2_cpp::Writer>();
    writer_->open(bag_file_path_);

    for (YAML::const_iterator it = topics.begin(); it != topics.end(); ++it)
    {
      // get name of the topic
      std::string topic_name = (*it)["name"].as<std::string>();

      // get type of the topic
      std::string topic_type = (*it)["type"].as<std::string>();

      RCLCPP_INFO(this->get_logger(), "topic_name: %s, topic_type: %s",
                  topic_name.c_str(), topic_type.c_str());

      // create the subscriber
      if (topic_type == "can_msgs/msg/Frame")
      {
        auto callback = create_callback(topic_name, topic_type);
        auto subscription = create_subscription<can_msgs::msg::Frame>(topic_name, 10, callback);
        subscriptions_.push_back(subscription);
      }
      else if (topic_type == "udp_msgs/msg/UdpPacket")
      {
        auto callback = create_callback(topic_name, topic_type);
        auto subscription = create_subscription<udp_msgs::msg::UdpPacket>(topic_name, 10, callback);
        subscriptions_.push_back(subscription);
      }
    }
  }

private:
  // I want to create a function which can product callback function!
  std::function<void(std::shared_ptr<rclcpp::SerializedMessage>)> create_callback(const std::string &topic_name,
                                                                                  const std::string &topic_type)
  {
    auto callback = [this, topic_name, topic_type](std::shared_ptr<rclcpp::SerializedMessage> msg)
    {
      rclcpp::Time time_stamp = this->now();
      if (topic_type == "can_msgs/msg/Frame")
      {
        rclcpp::Serialization<can_msgs::msg::Frame> serialization;
        can_msgs::msg::Frame can_msg;
        serialization.deserialize_message(msg.get(), &can_msg);
        time_stamp = can_msg.header.stamp;
      }
      else if (topic_type == "udp_msgs/msg/UdpPacket")
      {
        rclcpp::Serialization<udp_msgs::msg::UdpPacket> serialization;
        udp_msgs::msg::UdpPacket udp_msg;
        serialization.deserialize_message(msg.get(), &udp_msg);
        time_stamp = udp_msg.header.stamp;
      }

      RCLCPP_INFO(this->get_logger(), "time_stamp.seconds = %.2f, time_stamp.nanoseconds = %ld",
                  time_stamp.seconds(), time_stamp.nanoseconds());

      this->writer_->write(msg, topic_name, topic_type, time_stamp);
    };
    return callback;
  }

  std::string bag_file_path_; // path of storage folder
  std::unique_ptr<rosbag2_cpp::Writer> writer_;
  std::vector<std::shared_ptr<void>> subscriptions_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TopicRecorder>());
  rclcpp::shutdown();
  return 0;
}