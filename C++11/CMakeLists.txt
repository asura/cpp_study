cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(
  cppstudy
  LANGUAGES CXX
)

# C++規格
set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)

add_executable(
  TesterCpp11
  Tester.cpp
  thread.test.cpp
)

target_include_directories(
  TesterCpp11
  PRIVATE ${PROJECT_SOURCE_DIR}/../third_party/Catch2/single_include
  PRIVATE ${PROJECT_SOURCE_DIR}/../vendor/plog/include
)

target_link_libraries(
  TesterCpp11
  Threads::Threads
)
