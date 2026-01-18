cmake_minimum_required(VERSION 3.20)
project(data_structures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(string)
add_subdirectory(array-pointers)
add_subdirectory(linked-list)
add_subdirectory(stack-queue)
add_subdirectory(tree-graph-search)
add_subdirectory(heap)
add_subdirectory(hash-table)
