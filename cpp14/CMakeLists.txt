cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(
    Cpp14_DSA VERSION 1.0
    DESCRIPTION "My Implementaion of data structures and algorithms in C++"
    LANGUAGES CXX
)

add_executable("${PROJECT_NAME}" main.cpp)

add_subdirectory("Dynamic Array")
target_link_libraries("${PROJECT_NAME}" DynamicArray)

