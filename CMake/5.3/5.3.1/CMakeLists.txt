# 设置CMake的最低版本
cmake_minimum_required(VERSION 3.0)

# 设置项目名称
project(HELLOWORLD)

# 生成可执行文件
add_executable(helloWorld_CMake helloworld.c)

# 使用CMake外部构建
# 在项目目录下新建一个build目录
# 然后在build目录下使用 cmake .. 命令来进行编译产生makefile
# 然后再在build目录下使用make生成可执行文件