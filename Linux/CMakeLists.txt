cmake_minimum_required(VERSION 3.6)
project(Linux)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES socket_http.c)

add_executable(Linux ${SOURCE_FILES})
