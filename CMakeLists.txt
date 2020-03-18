cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(cpp_study)

# C++規格
set(CMAKE_CXX_STANDARD 17)

find_library(TCMALLOC_PATH tcmalloc)
find_library(CLANG_PATH clang)

add_subdirectory(include)
add_subdirectory(exam)
