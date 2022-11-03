cmake_minimum_required(VERSION 3.13)
project(list)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp indexes.cpp insertion.cpp list.cpp log.cpp otheropers.cpp pointers.cpp verification.cpp)

add_executable(list ${SOURCE_FILES})