cmake_minimum_required(VERSION 3.21)
project(MyShellHW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(MyShellHW main.cpp shelpers.cpp shelpers.h)

set(GCC_COVERAGE_COMPILE_FLAGS "-lreadline")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")