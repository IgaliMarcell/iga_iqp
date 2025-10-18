from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='iga_iqp',
            executable='gps_publisher_node',
            name='gps_publisher_node',
            output='screen'
        ),
        Node(
            package='iga_iqp',
            executable='path_visualizer_node',
            name='path_visualizer_node',
            output='screen'
        ),
    ])