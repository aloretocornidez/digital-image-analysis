cmake_minimum_required(VERSION 3.5)

project(homework-5 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-function -Wno-unused-parameter -Wextra -std=c++11")

set(SOURCES
    src/main.cpp
    src/functions.cpp
    src/functions.hpp

)

add_executable(homework-5 ${SOURCES})


# This includes the header files that I make.
target_include_directories(homework-5
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# This includes the opencv headerfiles.
find_package( OpenCV REQUIRED )
# include_directories( ${OpenCV_INCLUDE_DIRS}/src )
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( homework-5 ${OpenCV_LIBS} )


