cd ~/ros2_ws/

colcon build --packages-select iga_iqp --symlink-install

source ~/ros2_ws/install/setup.bash

ros2 launch iga_iqp gps_path_visualizer.launch.py

rviz2 -> add Marker -> topic = /visualization_marker && fixed frame = map
