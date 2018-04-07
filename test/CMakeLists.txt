include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/test
  ${PROJECT_SOURCE_DIR}/vendor/Catch/single_include
  vendor/gflags/include
  ${PROJECT_SOURCE_DIR}/vendor/plog/include)

add_executable(Tester tester.cpp
  ConstructorVSFactoryMethodTest.cpp
  SplitString.cpp
  optional.cpp
  shared_ptr.cpp
  thread_safe_queue.cpp
  cli/gflags.cpp
)

target_link_libraries(
  Tester
  CppStudy
  gflags
)
