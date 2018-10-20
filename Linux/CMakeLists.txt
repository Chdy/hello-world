cmake_minimum_required(VERSION 3.6)
project(Linux)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES socketpair_msgget_server.c)

add_executable(Linux ${SOURCE_FILES})
