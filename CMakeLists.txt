cmake_minimum_required(VERSION 3.15)
project(RoadRecovery98)

set(cmake_cxx_standard 98)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#use ASan to analyze address-related issues (e.g., memory leak) and strict C++98 standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O -pedantic-errors -std=c++98")

#set(CMAKE_CXX_FLAGS "")

add_subdirectory(src)