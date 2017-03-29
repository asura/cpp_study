include_directories(${PROJECT_SOURCE_DIR}/UnitTest)

add_executable(Tester tester.cpp catch.hpp
  shared_ptr.cpp
)
