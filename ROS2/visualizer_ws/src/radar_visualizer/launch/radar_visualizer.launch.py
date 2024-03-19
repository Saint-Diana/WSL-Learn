from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    config = os.path.join(
        get_package_share_directory('radar_visualizer'),
        'config',
        'config.yaml'
    )

    radar_visulizer_node = Node(
        package='radar_visualizer',
        executable='radar_visualizer',
        name='radar_visulizer_node',
        parameters=[config]
    )

    return LaunchDescription([
        radar_visulizer_node
    ])