from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
import os

def generate_launch_description():
    rviz_config_file = os.path.join(
        os.path.dirname(__file__),
        'markers.rviz'
    )
    
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
        # RViz2 indítása
        ExecuteProcess(
            cmd=['rviz2', '-d', rviz_config_file],
            output='screen'
        ),
    ])