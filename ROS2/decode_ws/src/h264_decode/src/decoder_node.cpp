#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/byte_multi_array.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include "h264decoder.h"

class H264Decoder : public rclcpp::Node
{
public:
    H264Decoder()
        : Node("h264_decoder")
    {
        m_h264Decoder_.initial();

        sub_topic_ = this->declare_parameter<std::string>("sub_topic", "");
        pub_topic_ = this->declare_parameter<std::string>("pub_topic", "");

        sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            sub_topic_, 10, std::bind(&H264Decoder::callback, this, std::placeholders::_1));
        pub_ = this->create_publisher<sensor_msgs::msg::Image>(pub_topic_, 10);
    }

private:
    void callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        try
        {
            uint8_t *data = msg->data.data();
            int size = msg->data.size();
            cv::Mat dst;

            m_h264Decoder_.decode(data, size, dst);

            // 再把 BGR 转回 YUV422_YUY2
            cv::Mat dst_yuv;
            cv::cvtColor(dst, dst_yuv, cv::COLOR_BGR2YUV);
            cv::Mat dst_yuv422_yuy2;
            yuv2yuv422_yuy2(dst_yuv, dst_yuv422_yuy2);

            int dst_pixelType = dst.type();
            // get depth and channels
            int depth = CV_MAT_DEPTH(dst_pixelType);
            int channels = CV_MAT_CN(dst_pixelType);
            RCLCPP_INFO(this->get_logger(), "pixel type: %d, depth: %d, channels: %d", dst_pixelType, depth, channels);

            auto decoded_msg = cv_bridge::CvImage(msg->header, sensor_msgs::image_encodings::YUV422_YUY2, dst_yuv422_yuy2).toImageMsg();
            decoded_msg->header = msg->header;
            decoded_msg->height = msg->height;
            decoded_msg->width = msg->width;
            decoded_msg->is_bigendian = msg->is_bigendian;
            decoded_msg->step = msg->step;
            pub_->publish(*decoded_msg);
        }
        catch (const cv::Exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "OpenCV error: %s", e.what());
        }
    }

    void yuv2yuv422_yuy2(const cv::Mat &src, cv::Mat &dst)
    {
        // 确保源图像是YUV格式
        CV_Assert(src.type() == CV_8UC3);

        // 初始化目标图像
        dst.create(src.rows, src.cols, CV_8UC2);

        for (int i = 0; i < src.rows; ++i)
        {
            for (int j = 0; j < src.cols; j += 2)
            {
                // 获取YUV图像的像素值
                cv::Vec3b pixel1 = src.at<cv::Vec3b>(i, j);
                cv::Vec3b pixel2 = src.at<cv::Vec3b>(i, j + 1);

                // YUV422_YUY2格式中，U和V是共享的
                uchar Y1 = pixel1[0];
                uchar U = pixel1[1];
                uchar Y2 = pixel2[0];
                uchar V = pixel1[2];

                // 设置目标图像的像素值
                cv::Vec2b &dstPixel1 = dst.at<cv::Vec2b>(i, j);
                cv::Vec2b &dstPixel2 = dst.at<cv::Vec2b>(i, j + 1);

                dstPixel1[0] = Y1;
                dstPixel1[1] = U;
                dstPixel2[0] = Y2;
                dstPixel2[1] = V;
            }
        }
    }

    CH264Decoder m_h264Decoder_;
    std::string sub_topic_;
    std::string pub_topic_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<H264Decoder>());
    rclcpp::shutdown();
    return 0;
}