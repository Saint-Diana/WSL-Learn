#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/byte_multi_array.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include "h264encoder.h"

class H264Encoder : public rclcpp::Node
{
public:
    H264Encoder()
        : Node("h264_encoder")
    {
        conf_.width = 1280;
        conf_.height = 720;
        conf_.gop_size = 10;
        conf_.max_b_frames = 0;
        conf_.frame_rate = 10;
        h264_.Init(conf_);

        sub_topic_ = this->declare_parameter<std::string>("sub_topic", "");
        pub_topic_ = this->declare_parameter<std::string>("pub_topic", "");

        sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            sub_topic_, 10, std::bind(&H264Encoder::callback, this, std::placeholders::_1));
        pub_ = this->create_publisher<sensor_msgs::msg::Image>(pub_topic_, 10);
    }

private:
    void callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        try
        {
            // transfer ROS msg to OpenCV image
            cv_bridge::CvImagePtr cv_ptr; // YUV422_YUY2色彩空间 -> BGR -> YUV422_YUY2
            try
            {
                cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8); // here actually encoding transfers to BGR8
            }
            catch (cv_bridge::Exception &e)
            {
                RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            }
            cv::Mat src_image = cv_ptr->image;

            int src_pixelType = src_image.type();
            // get depth and channels
            int depth = CV_MAT_DEPTH(src_pixelType);
            int channels = CV_MAT_CN(src_pixelType);
            RCLCPP_INFO(this->get_logger(), "pixel type: %d, depth: %d, channels: %d", src_pixelType, depth, channels);

            // do encode
            AVPacket *pkt = h264_.encode(src_image);
            msg->data = std::vector<uint8_t>(pkt->data, pkt->data + pkt->size);
            msg->encoding = sensor_msgs::image_encodings::BGR8;
            pub_->publish(*msg);
        }
        catch (cv_bridge::Exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        }
    }

    h264Encoder h264_;
    AvH264EncConfig conf_;
    std::string sub_topic_;
    std::string pub_topic_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<H264Encoder>());
    rclcpp::shutdown();
    return 0;
}