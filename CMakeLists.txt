cmake_minimum_required(VERSION 3.15)
project(RoadRecovery98)

set(cmake_cxx_standard 98)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#use ASan
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

set(CMAKE_CXX_FLAGS "-pedantic-errors -std=c++98")

add_subdirectory(src)