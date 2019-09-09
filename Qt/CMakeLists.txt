cmake_minimum_required(VERSION 3.10)
project(Qt)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp mainwindow.cpp)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

#如果你的项目包含qrc文件，那么需要将它们单独添加进来
add_executable(Qt ${SOURCE_FILES} icon.qrc) #需要重新qmake
#target_link_libraries(Qt Qt5::Core)
target_link_libraries(Qt Qt5::Widgets)
