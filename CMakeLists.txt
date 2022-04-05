cmake_minimum_required(VERSION 3.16)
project(APT_A1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(APT_A1
        main.cpp
        milestone4.cpp
        milestone4.h
        Node.cpp
        Node.h
        NodeList.cpp
        NodeList.h
        PathPlanner.cpp
        PathPlanner.h
        Types.h)
