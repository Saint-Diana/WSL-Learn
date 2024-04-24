#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/trigger.hpp"

class ReplayClientNode : public rclcpp::Node
{
public:
    ReplayClientNode() : Node("replay_client_node")
    {
        client_ = this->create_client<std_srvs::srv::Trigger>("replay");
    }

    void send_request()
    {
        auto request = std::make_shared<std_srvs::srv::Trigger::Request>();
        auto result = client_->async_send_request(request);
        // 等待服务端响应
        if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) ==
            rclcpp::FutureReturnCode::SUCCESS)
        {
            RCLCPP_INFO(this->get_logger(), "Replay response: %s", result.get()->message.c_str());
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to call service replay");
        }
    }

private:
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr client_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ReplayClientNode>();
    node->send_request();
    rclcpp::shutdown();
    return 0;
}
