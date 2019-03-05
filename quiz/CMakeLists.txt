cmake_minimum_required(VERSION 3.12)
project(quiz)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -Wextra")

add_executable(quiz main.cpp)