cmake_minimum_required(VERSION 3.10)
project(Qt)

set(CMAKE_CXX_STANDARD 11)

#add_executable(Qt main.cpp)

set(SOURCE_FILES main.cpp gotocelldialog.cpp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
add_executable(Qt ${SOURCE_FILES})
#target_link_libraries(Qt Qt5::Core)
target_link_libraries(Qt Qt5::Widgets)
