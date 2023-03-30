cmake_minimum_required(VERSION 3.5)

project(homework-5 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-function -Wno-unused-parameter -Wextra -std=c++11")




# Source code
# add_subdirectory( src )

add_executable(homework-5 src/main.cpp src/functions.hpp src/functions.cpp)

# Adding Open CV Library
# find_package( OpenCV REQUIRED )
# target_include_directories(homework-5 PUBLIC ${OpenCV_INCLUDE_DIRS})
# target_link_libraries(homework-5 ${OpenCV_LIBS})

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS}/src )
include_directories( ${OpenCV_INCLUDE_DIRS})
target_link_libraries( homework-5 ${OpenCV_LIBS} )
