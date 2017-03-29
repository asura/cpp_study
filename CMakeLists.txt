cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(cpp_study)

include(cmake/flags.cpp.std.cmake)

add_subdirectory(Benchmark)
add_subdirectory(UnitTest)
