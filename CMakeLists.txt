cmake_minimum_required(VERSION 3.15)
project(RoadRecovery98)

set(CMAKE_CXX_STANDARD 98)

set(NJU_ICS
    "src/nju/ics")

set(NJU_ICS_HEADER
    "${NJU_ICS}/algorithm/include/"
    "${NJU_ICS}/entity/include/"
    "${NJU_ICS}/main/include/"
    "${NJU_ICS}/tool/include/")

set(NJU_ICS_CPP
    "${NJU_ICS}/algorithm/"
    "${NJU_ICS}/entity/"
    "${NJU_ICS}/main/"
    "${NJU_ICS}/tool/")

add_executable(RoadRecovery98 ${NJU_ICS}/main/main.cpp ${NJU_ICS_CPP} ${NJU_ICS_HEADER})
