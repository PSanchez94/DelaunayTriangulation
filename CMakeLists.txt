cmake_minimum_required(VERSION 3.15)
project(DelaunayTriangulation)

set(CMAKE_CXX_STANDARD 11)

add_executable(DelaunayTriangulation main.cpp)

add_subdirectory(DelaunayT)
add_subdirectory(DelaunayTests)
