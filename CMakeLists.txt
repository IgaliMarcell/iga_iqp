cmake_minimum_required(VERSION 3.8)
project(iga_iqp)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)

add_executable(gps_publisher_node src/gps_publisher_node.cpp)
ament_target_dependencies(gps_publisher_node rclcpp geometry_msgs)

add_executable(path_visualizer_node src/path_visualizer_node.cpp)
ament_target_dependencies(path_visualizer_node rclcpp geometry_msgs visualization_msgs)

install(TARGETS
  gps_publisher_node
  path_visualizer_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()