include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/UnitTest)

add_executable(Tester tester.cpp catch.hpp
  SplitString.cpp
  shared_ptr.cpp
  thread_safe_queue.cpp
)

target_link_libraries(
  Tester
  CppStudy
)
