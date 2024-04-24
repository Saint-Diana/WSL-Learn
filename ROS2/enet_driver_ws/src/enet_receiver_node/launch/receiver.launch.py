from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, TextSubstitution

def generate_launch_description():
    enet_receiver_node = Node(
        package='enet_receiver_node',
        executable='enet_receiver_node',
        name='enet_receiver_node',
        namespace=TextSubstitution(text=''),
        parameters=[{
            'sub_topic_name': LaunchConfiguration('pub_topic_name'),
            'server_port': LaunchConfiguration('server_port'),
        }],
        output='screen',
    )

    return LaunchDescription([
        DeclareLaunchArgument('pub_topic_name', default_value='/lidar'),
        DeclareLaunchArgument('server_port', default_value='6666'),
        enet_receiver_node,
    ])