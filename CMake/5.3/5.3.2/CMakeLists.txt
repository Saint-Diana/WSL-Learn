cmake_minimum_required(VERSION 3.0)

project(SWAP)

set(SRC main.cpp ./src/swap.cpp)

add_compile_options(-Wall -g -O2 -std=c++11)

include_directories(./headers)

add_executable(main_cmake ${SRC})