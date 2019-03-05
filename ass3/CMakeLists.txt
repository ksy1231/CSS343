cmake_minimum_required(VERSION 3.12)
project(ass3)

set(CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -Wextra")

add_executable(ass3 ass3.cpp graph.cpp graph.h vertex.cpp vertex.h edge.cpp edge.h)