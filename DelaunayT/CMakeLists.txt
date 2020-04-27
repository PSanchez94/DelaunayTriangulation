cmake_minimum_required(VERSION 3.15)
project(DelaunayT)

set(CMAKE_CXX_STANDARD 11)

set(Headers
        inc/Vertex.hpp
        inc/Vector.hpp
        inc/Triangle.hpp
        inc/DelaunayT.hpp)

include_directories(${PROJECT_SOURCE_DIR}/inc)

add_library(${PROJECT_NAME} SHARED ${Headers})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)