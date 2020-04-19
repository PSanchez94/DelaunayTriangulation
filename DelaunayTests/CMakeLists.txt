cmake_minimum_required(VERSION 3.15)
project(DelaunayTests)

set(CMAKE_CXX_STANDARD 11)

set(Sources
        VectorTest.cpp
        VertexTest.cpp)



add_subdirectory(googletest)

include_directories(../DelaunayT/inc)

add_executable(${PROJECT_NAME} ${Sources})
target_link_libraries(${PROJECT_NAME} PUBLIC
        gtest_main
        DelaunayT)

add_test(
        NAME ${PROJECT_NAME}
        COMMAND ${PROJECT_NAME}
)

