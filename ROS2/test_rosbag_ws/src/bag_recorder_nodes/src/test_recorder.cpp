#include <rclcpp/rclcpp.hpp>
#include "rosbag2_transport/recorder.hpp"
#include <rosbag2_transport/record_options.hpp>
#include <rosbag2_storage/storage_options.hpp>
#include <rosbag2_cpp/writer.hpp>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    RCLCPP_INFO(rclcpp::get_logger("main"), "ROS 2 node initialized successfully.");

    rosbag2_transport::RecordOptions record_options;
    record_options.topics = {"/topic"};
    record_options.rmw_serialization_format = rmw_get_serialization_format();
    record_options.compression_format = "zstd";
    record_options.compression_mode = "file";

    rosbag2_storage::StorageOptions storage_options{"recorder_bag", "sqlite3"};

    auto writer_ = std::make_shared<rosbag2_cpp::Writer>();
    auto recorder = std::make_shared<rosbag2_transport::Recorder>(std::move(writer_), storage_options, record_options, "record_node");

    recorder->record();

    while (rclcpp::ok())
    {
        RCLCPP_INFO(rclcpp::get_logger("main"), "Recording!");
    }

    recorder.reset();
    rclcpp::shutdown();
    return 0;
}