from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, TextSubstitution

def generate_launch_description():
    replay_server_node = Node(
        package='replay_server',
        executable='replay_server_node',
        name='replay_server_node',
        namespace=TextSubstitution(text=''),
        parameters=[{
            'bag_path': LaunchConfiguration('bag_path'),
        }],
        output='screen',
    )

    return LaunchDescription([
        DeclareLaunchArgument('bag_path', default_value='~/pointcloud'),
        replay_server_node,
    ])