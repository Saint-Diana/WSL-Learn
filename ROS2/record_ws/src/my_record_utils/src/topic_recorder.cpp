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
    for (YAML::const_iterator it = topics.begin(); it != topics.end(); ++it)
    {
      // RCLCPP_INFO(this->get_logger(), "name: %s, age: %d", (*it)["name"].as<std::string>().c_str(), (*it)["type"].as<int>());
      std::string topic_name = (*it)["name"].as<std::string>();
      int topic_type = (*it)["type"].as<int>();
      switch (topic_type)
      {
        case 0:
        {
          auto subscription = create_subscription<can_msgs::msg::Frame>(topic_name, 10, std::bind(&TopicRecorder::can_msg_callback, this, std::placeholders::_1));
          subscriptions_.push_back(subscription);
          break;
        }
      }
    }

    // initialize writer_
    writer_ = std::make_unique<rosbag2_cpp::Writer>();
    writer_->open(bag_file_path_);
  }

private:
  void can_msg_callback(std::shared_ptr<rclcpp::SerializedMessage> msg) const
  {
    rclcpp::Time time_stamp = this->now();
    writer_->write(msg, "can_message", "can_msgs/msg/Frame", time_stamp); // TODO: extract "can_message" to a parameter
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