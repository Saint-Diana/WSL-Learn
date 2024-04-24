from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, TextSubstitution


def generate_launch_description():
    encoder_node_1 = Node(
        package='h264_encode',
        executable='encoder_node',
        name='h264_encoder_node',
        namespace=TextSubstitution(text='camera1'),
        parameters=[{
            'sub_topic': LaunchConfiguration('sub_topic_1'),
            'pub_topic': LaunchConfiguration('pub_topic_1'),
        }],
        output='screen',
    )

    encoder_node_2 = Node(
        package='h264_encode',
        executable='encoder_node',
        name='h264_encoder_node',
        namespace=TextSubstitution(text='camera2'),
        parameters=[{
            'sub_topic': LaunchConfiguration('sub_topic_2'),
            'pub_topic': LaunchConfiguration('pub_topic_2'),
        }],
        output='screen',
    )

    return LaunchDescription([
        DeclareLaunchArgument('sub_topic_1', default_value='/camera1/image_raw'),
        DeclareLaunchArgument('pub_topic_1', default_value='/camera1/image_encoded'),
        DeclareLaunchArgument('sub_topic_2', default_value='/camera2/image_raw'),
        DeclareLaunchArgument('pub_topic_2', default_value='/camera2/image_encoded'),
        encoder_node_1,
        encoder_node_2,
    ])