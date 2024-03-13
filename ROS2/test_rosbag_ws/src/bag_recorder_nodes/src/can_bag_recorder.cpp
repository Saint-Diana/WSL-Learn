#include <rclcpp/rclcpp.hpp>
#include <can_msgs/msg/frame.hpp>
#include <rosbag2_cpp/writer.hpp>

using std::placeholders::_1;

class SimpleBagRecorder : public rclcpp::Node
{
public:
  SimpleBagRecorder()
  : Node("can_bag_recorder")
  {
    writer_ = std::make_unique<rosbag2_cpp::Writer>();

    writer_->open("can_bag");

    subscription_ = create_subscription<can_msgs::msg::Frame>(
      "can_message", 10, std::bind(&SimpleBagRecorder::topic_callback, this, _1));
  }

private:
  void topic_callback(std::shared_ptr<rclcpp::SerializedMessage> msg) const
  {
    rclcpp::Time time_stamp = this->now();
    writer_->write(msg, "can_message", "can_msgs/msg/Frame", time_stamp);
  }

  rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr subscription_;
  std::unique_ptr<rosbag2_cpp::Writer> writer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimpleBagRecorder>());
  rclcpp::shutdown();
  return 0;
}