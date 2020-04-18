cmake_minimum_required(VERSION 3.15)
project(DelaunayT)

set(CMAKE_CXX_STANDARD 11)

set(Headers
        inc/Vertex.hpp)

set(Sources
        src/Vertex.cpp)

include_directories(${PROJECT_SOURCE_DIR}/inc)

add_library(${PROJECT_NAME} SHARED ${Sources} ${Headers})