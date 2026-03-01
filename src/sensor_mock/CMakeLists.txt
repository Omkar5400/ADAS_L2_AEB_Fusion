cmake_minimum_required(VERSION 3.8)
project(sensor_mock)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 1. Find Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

# 2. Define the Executable
add_executable(radar_node src/radar_node.cpp)

# 3. Link Dependencies to the Executable
ament_target_dependencies(radar_node rclcpp geometry_msgs)

# 4. Install Instructions (Crucial for 'ros2 run')
install(TARGETS
  radar_node
  DESTINATION lib/${PROJECT_NAME}
)

# 5. Testing (Optional, but must come before ament_package)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(PROGRAMS
  src/camera_node.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
