cmake_minimum_required(VERSION 3.20)
project(qt_cmake)
#生成ui_*.h
set(CMAKE_AUTOUIC ON)
#生成资源文件
set(CMAKE_AUTORCC ON)
#生成信号槽代码
set(CMAKE_AUTOMOC ON)

#core;gui;network;widgets;sql
#find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Sql Network)
 
set(project_ui
	login.ui)

set(project_headers
	Device.h stdafx.h login.h)

set(project_sources
	Device.cpp stdafx.cpp main.cpp)

add_executable( ${PROJECT_NAME} ${project_ui} ${project_headers} ${project_sources})

#D:\QT1\6.5.0\msvc2019_64\lib\cmake\Qt6
target_link_libraries(${PROJECT_NAME}
Qt6::Widgets
Qt6::Network
)

#cmake -S . -B build -DQt6_DIR=D:/QT1/6.5.0/msvc2019_64/lib/cmake/Qt6 -DCMAKE_PREFIX_PATH=D:/QT1/6.5.0/msvc2019_64/lib/cmake
#cmake --build build
#自动复制依赖的动态库：PS D:\Desktop\test\build\Debug> D:/QT1/6.5.0/msvc2019_64/bin/windeployqt qt_cmake.exe