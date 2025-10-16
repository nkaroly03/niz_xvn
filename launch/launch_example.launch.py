from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='niz_xvn',
            executable='rand_str_node',
        ),
        Node(
            package='niz_xvn',
            executable='str_hasher_node',
        ),
    ])