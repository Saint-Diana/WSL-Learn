from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, EmitEvent,
                            RegisterEventHandler)
from launch.conditions import IfCondition
from launch.event_handlers import OnProcessStart
from launch.events import matches_action
from launch.substitutions import LaunchConfiguration, TextSubstitution
from launch_ros.actions import LifecycleNode
from launch_ros.event_handlers import OnStateTransition
from launch_ros.events.lifecycle import ChangeState
from lifecycle_msgs.msg import Transition


def generate_launch_description():
    udp_sender_node = LifecycleNode(
        package='udp_driver',
        executable='udp_sender_node_exe',
        name='udp_sender_node',
        namespace=TextSubstitution(text=''),
        parameters=[{
            'ip': LaunchConfiguration('ip'),
            'port': LaunchConfiguration('port'),
            'topic_name': LaunchConfiguration('topic_name'),
        }],
        output='screen')

    udp_sender_node_configure_event_handler = RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action=udp_sender_node,
            on_start=[
                EmitEvent(
                    event=ChangeState(
                        lifecycle_node_matcher=matches_action(udp_sender_node),
                        transition_id=Transition.TRANSITION_CONFIGURE,
                    ),
                ),
            ],
        ),
        condition=IfCondition(LaunchConfiguration('auto_configure')),
    )

    udp_sender_node_activate_event_handler = RegisterEventHandler(
        event_handler=OnStateTransition(
            target_lifecycle_node=udp_sender_node,
            start_state='configuring',
            goal_state='inactive',
            entities=[
                EmitEvent(
                    event=ChangeState(
                        lifecycle_node_matcher=matches_action(udp_sender_node),
                        transition_id=Transition.TRANSITION_ACTIVATE,
                    ),
                ),
            ],
        ),
        condition=IfCondition(LaunchConfiguration('auto_activate')),
    )

    return LaunchDescription([
        DeclareLaunchArgument('ip', default_value='192.168.1.31'),          # ip 是发送UDP datagrams的目标主机的ip
        DeclareLaunchArgument('port', default_value='6666'),                # port 是发送UDP datagrams的目标主机的端口
        DeclareLaunchArgument('topic_name', default_value='udp_message'),   # topic_name 是订阅的话题名称，也就是数据源的名称
        DeclareLaunchArgument('auto_configure', default_value='true'),
        DeclareLaunchArgument('auto_activate', default_value='true'),
        udp_sender_node,
        udp_sender_node_configure_event_handler,
        udp_sender_node_activate_event_handler,
    ])
