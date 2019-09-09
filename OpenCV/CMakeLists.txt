cmake_minimum_required(VERSION 3.10)
project(OpenCV)

find_package(OpenCV)
set(CMAKE_CXX_STANDARD 11)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(OpenCV face_detect.cpp)
target_link_libraries(OpenCV ${OpenCV_LIBS})