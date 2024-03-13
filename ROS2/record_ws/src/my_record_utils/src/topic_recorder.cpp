#include "rclcpp/rclcpp.hpp"
#include "rosbag2_cpp/writer.hpp"
#include "rcl_interfaces/msg/parameter_descriptor.hpp"
#include "can_msgs/msg/frame.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

typedef struct {
  std::string name;         // name of the topic
  int type;         // type of the topic(0 represents CAN Message; 1 represents Ethernet Message; 2 represents Compressed Video Stream)
}TopicInfo;

class TopicRecorder : public rclcpp::Node
{
public:
  TopicRecorder() : Node("topic_recorder")
  {
    // declare parameters in the yaml file
    auto topics_descriptor = rcl_interfaces::msg::ParameterDescriptor();
    topics_descriptor.description = "Topics needed to be recorded";
    this->declare_parameter("topics", rclcpp::ParameterValue(std::vector<uint8_t>{}), topics_descriptor);
    this->declare_parameter<std::string>("bag_file_path", "my_bag");

    // get parameters from the yaml file
    std::vector<uint8_t> topics_bytes;
    this->get_parameter("topics", topics_bytes);
    this->get_parameter("bag_file_path", bag_file_path_);

    std::vector<TopicInfo> topics_ = deserialize_topics(topics_bytes);

    // initialize writer_
    writer_ = std::make_unique<rosbag2_cpp::Writer>();
    writer_->open(bag_file_path_);

    for (const auto & topic_info : topics_)
    {
      // confirm the message type according to topic_info.type
      if (topic_info.type == 0)
      {
        auto subscription = this->create_subscription<can_msgs::msg::Frame>(topic_info.name, 10,
            std::bind(&TopicRecorder::can_msg_callback, this, std::placeholders::_1)); // TODO: how to transmit the parameter `topic_info.name` to the function `can_msg_callback`
        subscriptions_.push_back(subscription);
      }
    }
  }

private:
  void can_msg_callback(std::shared_ptr<rclcpp::SerializedMessage> msg) const
  {
    rclcpp::Time time_stamp = this->now();
    writer_->write(msg, "can_message", "can_msgs/msg/Frame", time_stamp); // TODO: change the "can_messgae" to a parameter which is declared above.
  }

  std::vector<TopicInfo> deserialize_topics(const std::vector<uint8_t>& bytes)
  {
    std::vector<TopicInfo> topics;
    std::string byte_string(bytes.begin(), bytes.end());
    std::istringstream stream(byte_string);
    std::string line;

    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      std::string name;
      int type;
      linestream >> name >> type;
      topics.push_back(TopicInfo{name, type});
    }

    return topics;
  }

  std::vector<TopicInfo> topics_;
  std::string bag_file_path_;
  std::unique_ptr<rosbag2_cpp::Writer> writer_;
  std::vector<std::shared_ptr<void>> subscriptions_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TopicRecorder>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

