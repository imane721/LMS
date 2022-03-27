cmake_minimum_required(VERSION 3.21)
project(IL_malloc)

set(CMAKE_CXX_STANDARD 14)

add_executable(IL_malloc myMalloc.cpp myMalloc.h MyHashTable.cpp MyHashTable.h Tester.cpp)
