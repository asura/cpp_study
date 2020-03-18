cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(cpp_study)

# C++規格
set(CMAKE_CXX_STANDARD 17)

find_library(TCMALLOC_PATH tcmalloc)

add_subdirectory(exam)
#add_subdirectory(lib)
#add_subdirectory(Benchmark)
#add_subdirectory(test)
#add_subdirectory(vendor/benchmark)
#add_subdirectory(vendor/gflags)
