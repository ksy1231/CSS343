cmake_minimum_required(VERSION 3.12)
project(ass4)

set (CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -Wextra")

add_executable(ass4 ass4.cpp classicmovie.cpp classicmovie.h comedymovie.cpp comedymovie.h customer.cpp customer.h customerlist.cpp customerlist.h dramamovie.cpp dramamovie.h history.cpp history.h movie.cpp movie.h moviefactory.cpp moviefactory.h movieinventory.cpp movieinventory.h movielist.cpp movielist.h store.cpp store.h)