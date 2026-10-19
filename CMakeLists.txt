cmake_minimum_required(VERSION 3.31)
project(streaming_algorithm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(streaming_algorithm src/main.cpp src/DGIM.cpp)
target_include_directories(streaming_algorithm PRIVATE include)