from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, TextSubstitution
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
    topic_recorder_node = Node(
        package='my_record_utils',                      # name of ROS2 package
        executable='topic_recorder',                    # name of executable file
        name='topic_recorder_node',                     # name of ROS2 node,
        namespace=TextSubstitution(text=''),
        parameters=[{
            'bag_file_path': LaunchConfiguration('bag_file_path'),
        }],
        output='screen',
    )

    return LaunchDescription([
        DeclareLaunchArgument('bag_file_path', default_value='record_message'),
        topic_recorder_node
    ])