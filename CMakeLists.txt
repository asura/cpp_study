cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(cpp_study)

# C++規格
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall")

find_library(TCMALLOC_PATH tcmalloc)
find_library(CLANG_PATH clang)

add_subdirectory(C++11)
add_subdirectory(C++14)
add_subdirectory(C++17)
add_subdirectory(C++20)
add_subdirectory(include)
add_subdirectory(exam)
