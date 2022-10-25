cmake_minimum_required(VERSION 3.13)  # CMake version check
project(list)               # Create project "list"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp log.cpp list.cpp listopers.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(list ${SOURCE_FILES})