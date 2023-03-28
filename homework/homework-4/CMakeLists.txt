cmake_minimum_required(VERSION 3.5)

project(opencv LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(kittler-illingworth src/main.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS}/src )
include_directories( ${OpenCV_INCLUDE_DIRS})

target_link_libraries( kittler-illingworth ${OpenCV_LIBS} )