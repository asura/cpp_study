cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(
  cppstudy
  LANGUAGES CXX
)

# C++規格 : C++20 requires cmake 3.12 or higher
set(CMAKE_CXX_STANDARD 20)

add_executable(
  Tester
  Tester.cpp
  version.cpp
)

target_include_directories(
  Tester
  PRIVATE ${PROJECT_SOURCE_DIR}/../third_party/Catch2/single_include
  PRIVATE ${PROJECT_SOURCE_DIR}/../vendor/plog/include
)
