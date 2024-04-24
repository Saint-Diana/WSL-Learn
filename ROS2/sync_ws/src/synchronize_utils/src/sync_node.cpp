#include <memory>

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <rclcpp/rclcpp.hpp>
#include <can_msgs/msg/frame.hpp>
#include <udp_msgs/msg/udp_packet.hpp>

class SyncNode : public rclcpp::Node
{
public:
  SyncNode() : Node("sync_node")
  {
    can_pub_ = this->create_publisher<can_msgs::msg::Frame>("sync_can", 10);
    udp_pub_ = this->create_publisher<udp_msgs::msg::UdpPacket>("sync_udp", 10);

    can_sub_.subscribe(this, "from_can_bus");
    udp_sub_.subscribe(this, "ethernet_message");

    sync_ = std::make_shared<message_filters::Synchronizer<SyncPolicy>>(SyncPolicy(10), can_sub_, udp_sub_);
    sync_->registerCallback(std::bind(&SyncNode::SyncCallback, this, std::placeholders::_1, std::placeholders::_2));

    RCLCPP_INFO(this->get_logger(), "Complete Constructor Function.");
  }

private:
  void SyncCallback(
      const can_msgs::msg::Frame::ConstSharedPtr &can_msg,
      const udp_msgs::msg::UdpPacket::ConstSharedPtr &udp_msg)
  {
    RCLCPP_INFO(this->get_logger(),
                "I heard and synchronized the following timestamps: %u, %u",
                can_msg->header.stamp.sec, udp_msg->header.stamp.sec);

    can_pub_->publish(*can_msg);
    udp_pub_->publish(*udp_msg);
  }

  message_filters::Subscriber<can_msgs::msg::Frame> can_sub_;
  message_filters::Subscriber<udp_msgs::msg::UdpPacket> udp_sub_;
  typedef message_filters::sync_policies::ApproximateTime<can_msgs::msg::Frame, udp_msgs::msg::UdpPacket> SyncPolicy;
  std::shared_ptr<message_filters::Synchronizer<SyncPolicy>> sync_;
  rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr can_pub_;
  rclcpp::Publisher<udp_msgs::msg::UdpPacket>::SharedPtr udp_pub_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SyncNode>());
  rclcpp::shutdown();
  return 0;
}