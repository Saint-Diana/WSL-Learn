cmake_minimum_required(VERSION 3.8)
project(h264_decode)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

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

include_directories(
  include/h264_decode
  ${OpenCV_INCLUDE_DIRS}  # 添加 OpenCV 的 include 路径
  ${cv_bridge_INCLUDE_DIRS}  # 添加 cv_bridge 的 include 路径
)

add_executable(decoder_node
  src/decoder_node.cpp
  src/h264decoder.cpp
)

target_link_libraries(decoder_node
  ${OpenCV_LIBRARIES}
  avformat avdevice
  avcodec
  avutil
  avfilter
  postproc
  swresample
  swscale
)

ament_target_dependencies(decoder_node
  rclcpp
  sensor_msgs
  std_msgs
  cv_bridge
  OpenCV
)

install(TARGETS decoder_node
        DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
