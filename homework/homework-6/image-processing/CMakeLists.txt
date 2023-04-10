cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "image-processing")

project(${PROJECT_NAME} LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(dilation)
add_subdirectory(erosion)



