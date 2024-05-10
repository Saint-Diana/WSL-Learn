#include <memory>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <rclcpp/rclcpp.hpp>
#include <can_msgs/msg/frame.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

class SyncNode : public rclcpp::Node
{
public:
  SyncNode() : Node("sync_node") // two channels of sensor_msgs::msg::Image, one channel of can_msgs::msg::Frame and one channel of sensor_msgs::msg::pointcloud2
  {
    image_pub_1_ = this->create_publisher<sensor_msgs::msg::Image>("/sync/camera1", 10);
    image_pub_2_ = this->create_publisher<sensor_msgs::msg::Image>("/sync/camera2", 10);
    can_pub_ = this->create_publisher<can_msgs::msg::Frame>("/sync/radar", 10);
    pointcloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/sync/lidar", 10);

    image_sub_1_.subscribe(this, "/camera1/image_decoded");
    image_sub_2_.subscribe(this, "/camera2/image_decoded");
    can_sub_.subscribe(this, "/can_message");
    pointcloud_sub_.subscribe(this, "/livox/lidar");

    sync_ = std::make_shared<message_filters::Synchronizer<SyncPolicy>>(
          SyncPolicy(10), image_sub_1_, image_sub_2_, can_sub_, pointcloud_sub_);
    sync_->registerCallback(std::bind(&SyncNode::SyncCallback,
          this, std::placeholders::_1, std::placeholders::_2,
          std::placeholders::_3, std::placeholders::_4));

    RCLCPP_INFO(this->get_logger(), "Complete Constructor Function.");
  }

private:
  void SyncCallback(
      const sensor_msgs::msg::Image::ConstPtr &image_msg_1,
      const sensor_msgs::msg::Image::ConstPtr &image_msg_2,
      const can_msgs::msg::Frame::ConstSharedPtr &can_msg,
      const sensor_msgs::msg::PointCloud2::ConstSharedPtr &pointcloud_msg)
  {
    RCLCPP_INFO(this->get_logger(),
                "I heard and synchronized the following timestamps:");
    RCLCPP_INFO(this->get_logger(), "/camera1/image_decoded: %u", image_msg_1->header.stamp.sec);
    RCLCPP_INFO(this->get_logger(), "/camera2/image_decoded: %u", image_msg_2->header.stamp.sec);
    RCLCPP_INFO(this->get_logger(), "/can_message: %u", can_msg->header.stamp.sec);
    RCLCPP_INFO(this->get_logger(), "/livox/lidar: %u", pointcloud_msg->header.stamp.sec);

    image_pub_1_->publish(*image_msg_1);
    image_pub_2_->publish(*image_msg_2);
    can_pub_->publish(*can_msg);
    pointcloud_pub_->publish(*pointcloud_msg);
  }

  message_filters::Subscriber<sensor_msgs::msg::Image> image_sub_1_;
  message_filters::Subscriber<sensor_msgs::msg::Image> image_sub_2_;
  message_filters::Subscriber<can_msgs::msg::Frame> can_sub_;
  message_filters::Subscriber<sensor_msgs::msg::PointCloud2> pointcloud_sub_;
  typedef message_filters::sync_policies::ApproximateTime<
      sensor_msgs::msg::Image, sensor_msgs::msg::Image,
      can_msgs::msg::Frame, sensor_msgs::msg::PointCloud2> SyncPolicy;
  std::shared_ptr<message_filters::Synchronizer<SyncPolicy>> sync_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_1_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_2_;
  rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr can_pub_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_pub_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SyncNode>());
  rclcpp::shutdown();
  return 0;
}