#include "rclcpp/rclcpp.hpp"
#include "radar_msgs/msg/radar_tracks.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "geometry_msgs/msg/point.hpp"

class RadarVisualizer: public rclcpp::Node
{
public:
    RadarVisualizer(): Node("radar_visualizer")
    {
        subscribe_topic_ = this->declare_parameter("subscribe_topic", "objects_raw");
        publish_topic_ = this->declare_parameter("publish_topic", "radar_tracks_markers");
        frame_id_ = this->declare_parameter("frame_id", "radar_tracks");
        namespace_ = this->declare_parameter("namespace", "radar_tracks");

        marker_id_ = 0;
        tracks_sub_ = this->create_subscription<radar_msgs::msg::RadarTracks>(
        subscribe_topic_, 10, std::bind(&RadarVisualizer::tracksCallback, this, std::placeholders::_1));
        visualizer_pub_ = this->create_publisher<visualization_msgs::msg::Marker>(publish_topic_, 10);
    }

private:
    void tracksCallback(const radar_msgs::msg::RadarTracks::SharedPtr tracks)
    {
        visualization_msgs::msg::Marker marker;
        marker.header.frame_id = frame_id_;
        marker.header.stamp = tracks->header.stamp;
        marker.ns = namespace_;
        marker.id = marker_id_++;
        marker.lifetime = rclcpp::Duration::from_seconds(4); // Point last for 4 seconds
        marker.type = visualization_msgs::msg::Marker::POINTS;
        marker.action = visualization_msgs::msg::Marker::ADD;
        marker.pose.orientation.w = 1.0;
        marker.scale.x = 0.1; // 根据实际情况调整大小
        marker.scale.y = 0.1;
        marker.color.r = 1.0;
        marker.color.g = 0.0;
        marker.color.b = 0.0;
        marker.color.a = 1.0;

        for (const auto& track: tracks->tracks)
        {
            geometry_msgs::msg::Point pt;
            pt.x = track.position.x;
            pt.y = track.position.y;
            pt.z = track.position.z;

            marker.points.push_back(pt);
        }

        visualizer_pub_->publish(marker);
    }

    rclcpp::Subscription<radar_msgs::msg::RadarTracks>::SharedPtr tracks_sub_;
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr visualizer_pub_;
    int marker_id_;
    std::string subscribe_topic_;
    std::string publish_topic_;
    std::string frame_id_;
    std::string namespace_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RadarVisualizer>());
    rclcpp::shutdown();
    return 0;
}