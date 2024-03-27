from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # create the node
    udp_bridge_node = Node(
        package='udp_driver',                                                           # name of ROS2 package
        executable='udp_bridge_node_exe',                                               # name of executable file
        name='udp_bridge_node',                                                         # name of ROS2 node
        output='screen',                                                                # where to display log
        parameters=[{'/home/shen/learn/ROS2/ethernet_ws/src/transport_drivers/udp_driver/params/udp_params.yml'}]       # path of configuration file
    )

    return LaunchDescription([
        udp_bridge_node
    ])