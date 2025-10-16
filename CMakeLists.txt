cmake_minimum_required(VERSION 3.8)
project(niz_xvn)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

set(ament_dependencies
  rclcpp
  std_msgs
  geometry_msgs
)

add_executable(rand_str_node src/rand_str.cpp)
ament_target_dependencies(rand_str_node ${ament_dependencies} )
add_executable(str_hasher_node src/str_hasher.cpp)
ament_target_dependencies(str_hasher_node ${ament_dependencies} )

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

install(TARGETS
rand_str_node
str_hasher_node
DESTINATION lib/${PROJECT_NAME}
)

ament_package()