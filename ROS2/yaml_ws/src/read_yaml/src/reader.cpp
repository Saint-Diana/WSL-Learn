#include "rclcpp/rclcpp.hpp"
#include <yaml-cpp/yaml.h>

class Reader: public rclcpp::Node
{
public:
    Reader(): Node("reader")
    {
        YAML::Node config = YAML::LoadFile("/home/shen/learn/ROS2/yaml_ws/src/read_yaml/config/config.yaml");
        YAML::Node topics = config["topics"];

        for (YAML::const_iterator it = topics.begin(); it != topics.end(); ++it)
        {
            RCLCPP_INFO(this->get_logger(), "name: %s, age: %d", (*it)["name"].as<std::string>().c_str(), (*it)["type"].as<int>());
        }
    }
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Reader>());
    rclcpp::shutdown();
    return 0;
}

