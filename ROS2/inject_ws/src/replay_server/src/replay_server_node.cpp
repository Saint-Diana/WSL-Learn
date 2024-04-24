#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>

class ReplayServerNode : public rclcpp::Node
{
public:
    ReplayServerNode() : Node("replay_server_node")
    {
        bag_path_ = this->declare_parameter("bag_path", "~/record_bag");

        service_ = this->create_service<std_srvs::srv::Trigger>(
            "replay",
            std::bind(
                &ReplayServerNode::handle_service, this,
                std::placeholders::_1, std::placeholders::_2));
    }

private:
    void handle_service(
        const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
        std::shared_ptr<std_srvs::srv::Trigger::Response> response)
    {
        (void)request;
        RCLCPP_INFO(this->get_logger(), "Received replay request");

        // 执行ros2 bag play命令
        std::string cmd = "ros2 bag play " + bag_path_;
        int result = system(cmd.c_str());
        if (result == 0)
        {
            RCLCPP_INFO(this->get_logger(), "Succeeded to execute Command[%s].\n", cmd.c_str());
            response->success = true;
            response->message = "Succeeded to replay";
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to execute Command[%s].\n", cmd.c_str());
            response->success = false;
            response->message = "Failed to replay";
        }
    }

    std::string bag_path_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr service_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ReplayServerNode>());
    rclcpp::shutdown();
    return 0;
}
