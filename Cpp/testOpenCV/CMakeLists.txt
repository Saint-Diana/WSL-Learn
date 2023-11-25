cmake_minimum_required(VERSION 3.0)
project(OPENCVTEST)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

# 寻找OpenCV库
find_package(OpenCV 4.7.0 REQUIRED)

# 添加你的源文件
set(SOURCES main.cpp)

# 创建可执行文件
add_executable(main ${SOURCES})

# 包含OpenCV头文件目录
target_include_directories(main PRIVATE ${OpenCV_INCLUDE_DIRS})

# 链接OpenCV库
target_link_libraries(main ${OpenCV_LIBS})