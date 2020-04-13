cmake_minimum_required(VERSION 3.15)
project(RoadRecovery98)

set(cmake_cxx_standard 98)

#set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

add_subdirectory(src)