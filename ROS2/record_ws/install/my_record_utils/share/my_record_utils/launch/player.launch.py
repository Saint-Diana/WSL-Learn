from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    config = os.path.join(
        get_package_share_directory('my_record_utils'),
        'config',
        'config.yaml'
    )

    # create the node
    topic_player_node = Node(
        package='my_record_utils',                      # name of ROS2 package
        executable='topic_player',                    # name of executable file
        name='topic_player_node',                     # name of ROS2 node
        parameters=[config]                             # path of configuration file
    )

    return LaunchDescription([
        topic_player_node
    ])