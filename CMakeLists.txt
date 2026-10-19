cmake_minimum_required(VERSION 3.31)
project(DGIM-algorithm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(DGIM-algorithm src/main.cpp src/DGIM.cpp)
target_include_directories(DGIM-algorithm PRIVATE include)