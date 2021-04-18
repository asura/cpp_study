cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(
  cppstudy
  LANGUAGES CXX
)

# C++規格
set(CMAKE_CXX_STANDARD 14)

add_executable(
  TesterCpp14
  Tester.cpp
  unique_ptr.test.cpp
)

target_include_directories(
  TesterCpp14
  PRIVATE ${PROJECT_SOURCE_DIR}/../third_party/Catch2/single_include
  PRIVATE ${PROJECT_SOURCE_DIR}/../vendor/plog/include
)
