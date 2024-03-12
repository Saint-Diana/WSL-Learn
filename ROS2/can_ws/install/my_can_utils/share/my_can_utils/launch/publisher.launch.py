from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    config = os.path.join(
        get_package_share_directory('my_can_utils'),
        'config',
        'publisher.yaml'
    )

    # create the node
    can_publisher_node = Node(
        package='my_can_utils',                 # name of ROS2 package
        executable='can_publisher',             # name of executable file
        name='can_publisher_node',                   # name of ROS2 node
        parameters=[config]
    )

    return LaunchDescription([
        can_publisher_node
    ])