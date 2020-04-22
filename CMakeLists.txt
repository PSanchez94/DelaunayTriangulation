cmake_minimum_required(VERSION 3.15)
project(DelaunayTriangulation)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(DelaunayT)
add_subdirectory(DelaunayTests)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/DelaunayT/inc
        ${OPENGL_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIR}
        )

add_executable(DelaunayTriangulation main.cpp)

target_link_libraries(DelaunayTriangulation DelaunayT ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
