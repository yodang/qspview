cmake_minimum_required(VERSION 3.16)

project(QspView CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_options(-O3 -Wall)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
#qt_standard_project_setup()

#add_executable(qspview src/qsp.cpp)

add_executable(qspgui src/main.cpp src/gui.cpp src/searchdialog.cpp src/qsp.cpp)

target_link_libraries(qspgui PRIVATE Qt5::Widgets)