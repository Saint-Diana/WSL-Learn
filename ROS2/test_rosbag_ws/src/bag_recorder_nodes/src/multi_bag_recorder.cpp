#include <rclcpp/rclcpp.hpp>
#include <can_msgs/msg/frame.hpp>
#include <std_msgs/msg/string.hpp>
#include <rosbag2_cpp/writer.hpp>

using std::placeholders::_1;

class SimpleBagRecorder : public rclcpp::Node
{
public:
  SimpleBagRecorder()
  : Node("can_bag_recorder")
  {
    writer_ = std::make_unique<rosbag2_cpp::Writer>();

    writer_->open("multi_bag");

    auto subscription_1 = create_subscription<can_msgs::msg::Frame>(
      "can_message", 10, std::bind(&SimpleBagRecorder::can_callback, this, _1));
    auto subscription_2 = create_subscription<std_msgs::msg::String>(
      "string_message", 10, std::bind(&SimpleBagRecorder::string_callback, this, _1));
    subscriptions_.push_back(subscription_1);
    subscriptions_.push_back(subscription_2);
  }

private:
  void can_callback(std::shared_ptr<rclcpp::SerializedMessage> msg) const
  {
    rclcpp::Time time_stamp = this->now();
    writer_->write(msg, "can_message", "can_msgs/msg/Frame", time_stamp);
  }

  void string_callback(std::shared_ptr<rclcpp::SerializedMessage> msg) const
  {
    rclcpp::Time time_stamp = this->now();
    writer_->write(msg, "string_message", "std_msgs/msg/String", time_stamp);
  }

  std::vector<std::shared_ptr<void>> subscriptions_;
  std::unique_ptr<rosbag2_cpp::Writer> writer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimpleBagRecorder>());
  rclcpp::shutdown();
  return 0;
}