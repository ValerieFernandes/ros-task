cmake_minimum_required(VERSION 3.5)
project(limo_control)

# C++ settings:
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -g)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2 REQUIRED)

add_executable(controller_node src/controller_node.cpp)

ament_target_dependencies(controller_node
  rclcpp
  geometry_msgs
  nav_msgs
  tf2
)
install(TARGETS
  controller_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()