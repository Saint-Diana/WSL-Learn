cmake_minimum_required(VERSION 3.0)

project(SOLDIERSORTIE)

include_directories(include)

set(SRC main.cpp src/gun.cpp src/soldier.cpp)

add_compile_options(-g)

add_executable(main ${SRC})