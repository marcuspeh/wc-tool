cmake_minimum_required(VERSION 3.8)
project(ccwc)

# Set C++17 as the standard for the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add an executable with the given sources
add_executable(ccwc ccwc.cpp FileInputException.cpp InvalidOptionException.cpp Options.cpp)
