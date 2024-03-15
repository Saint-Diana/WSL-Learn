from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    config = os.path.join(
        get_package_share_directory('my_ethernet_utils'),
        'config',
        'config.yaml'
    )

    # create the node
    ethernet_publisher_node = Node(
        package='my_ethernet_utils',        # name of ROS2 package
        executable='udp_publisher',         # name of executable file
        name='ethernet_publisher_node',     # name of ROS2 node
        parameters=[config]                 # path of configuration file
    )

    return LaunchDescription([
        ethernet_publisher_node
    ])