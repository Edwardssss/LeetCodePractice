cmake_minimum_required(VERSION 3.20)
project(algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(sorting)
add_subdirectory(search)
add_subdirectory(graph-theory)
add_subdirectory(dynamic-programming)
add_subdirectory(basic-tech-math)
