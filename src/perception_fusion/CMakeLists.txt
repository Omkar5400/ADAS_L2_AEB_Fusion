cmake_minimum_required(VERSION 3.8)
project(perception_fusion)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Find Eigen3
find_package(Eigen3 REQUIRED)

# Include the 'include' directory for our header file
include_directories(include)

# Create the executable using BOTH C++ files
add_executable(fusion_node 
  src/fusion_node.cpp 
  src/kalman_filter.cpp
)

# Link dependencies (Eigen3 is included here)
target_link_libraries(fusion_node Eigen3::Eigen)
ament_target_dependencies(fusion_node rclcpp geometry_msgs std_msgs)

# Install
install(TARGETS
  fusion_node
  DESTINATION lib/${PROJECT_NAME}
)

add_executable(decision_node src/decision_node.cpp)
ament_target_dependencies(decision_node rclcpp geometry_msgs std_msgs)

install(TARGETS
  decision_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
