include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/UnitTest
  ${PROJECT_SOURCE_DIR}/vendor/Catch/single_include
  ${PROJECT_SOURCE_DIR}/vendor/plog/include)

add_executable(Tester tester.cpp
  SplitString.cpp
  shared_ptr.cpp
  thread_safe_queue.cpp
)

target_link_libraries(
  Tester
  CppStudy
)
