cmake_minimum_required(VERSION 3.20)
project(others_two_pointers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")
foreach(child ${children})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${child}" AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${child}/main.cpp")
        add_executable(${child} "${child}/main.cpp")
        target_link_libraries(${child} PRIVATE GTest::gtest)
    endif()
endforeach()