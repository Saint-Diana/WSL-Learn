#include "rclcpp/rclcpp.hpp"
#include "rosbag2_cpp/writer.hpp"
#include "can_msgs/msg/frame.hpp"
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
      std::string topic_type = "unknowm";
      switch ((*it)["type"].as<int>())
      {
        case 0:
        {
          topic_type = "can_msgs/msg/Frame";
          break;
        }
      }

      // create the subscriber
      auto callback = create_callback(topic_name, topic_type);
      auto subscription = create_subscription<can_msgs::msg::Frame>(topic_name, 10, callback); // std::bind(&create_callback(topic_name, topic_type), this, std::placeholders::_1)
      subscriptions_.push_back(subscription);
    }
  }

private:
  // I want to create a function which can product callback function!
  std::function<void(std::shared_ptr<rclcpp::SerializedMessage>)> create_callback(const std::string& topic_name, const std::string& topic_type)
  {
    auto callback =[this, topic_name, topic_type](std::shared_ptr<rclcpp::SerializedMessage> msg)
    {
      rclcpp::Time time_stamp = this->now();
      this->writer_->write(msg, topic_name, topic_type, time_stamp);
    };
    return callback;
  }

  std::string bag_file_path_;                              // path of storage folder
  std::unique_ptr<rosbag2_cpp::Writer> writer_;
  std::vector<std::shared_ptr<void>> subscriptions_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TopicRecorder>());
  rclcpp::shutdown();
  return 0;
}