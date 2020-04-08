cmake_minimum_required(VERSION 3.15)
project(main)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(algorithm)
add_subdirectory(core)
add_subdirectory(entity)
add_subdirectory(tool)

add_executable(main main.cpp)

target_link_libraries(main core)