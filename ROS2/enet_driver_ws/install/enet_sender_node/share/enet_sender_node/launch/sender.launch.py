from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, TextSubstitution

def generate_launch_description():
    enet_sender_node = Node(
        package='enet_sender_node',
        executable='enet_sender_node',
        name='enet_sender_node',
        namespace=TextSubstitution(text=''),
        parameters=[{
            'sub_topic_name': LaunchConfiguration('sub_topic_name'),
            'server_ip': LaunchConfiguration('server_ip'),
            'server_port': LaunchConfiguration('server_port'),
        }],
        output='screen',
    )

    return LaunchDescription([
        DeclareLaunchArgument('sub_topic_name', default_value='/livox/lidar'),
        DeclareLaunchArgument('server_ip', default_value='127.0.0.1'),
        DeclareLaunchArgument('server_port', default_value='6666'),
        enet_sender_node,
    ])