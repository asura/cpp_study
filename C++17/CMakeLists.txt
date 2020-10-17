cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(
  cppstudy
  LANGUAGES CXX
)

# C++規格 : C++17 requires cmake 3.8 or higher
set(CMAKE_CXX_STANDARD 17)

add_executable(
  TesterCpp17
  Tester.cpp
  nodiscard.cpp
)

target_include_directories(
  TesterCpp17
  PRIVATE ${PROJECT_SOURCE_DIR}/../third_party/Catch2/single_include
  PRIVATE ${PROJECT_SOURCE_DIR}/../vendor/plog/include
)
