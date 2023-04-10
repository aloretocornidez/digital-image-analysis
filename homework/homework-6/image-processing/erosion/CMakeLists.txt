cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "erosion")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT_NAME})

add_library(${PROJECT_NAME}
    src/erosion.cpp
)
add_library(sub::erosion ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
PUBLIC ${PROJECT_SOURCE_DIR}/include)



# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-function -Wno-unused-parameter -Wextra -std=c++11")
# set(SOURCES
#     src/erosion.cpp

# )

# add_executable(${PROJECT_NAME} ${SOURCES})


# This includes the header files that I make.
# target_include_directories(${PROJECT_NAME}
#     PRIVATE
#     ${PROJECT_SOURCE_DIR}/include
# )

# # This includes the opencv headerfiles.
# find_package( OpenCV REQUIRED )
# # include_directories( ${OpenCV_INCLUDE_DIRS}/src )
# include_directories(${OpenCV_INCLUDE_DIRS})
# target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )


