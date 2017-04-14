include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/lib
  benchmark-1.1.0/include
  )

add_subdirectory(benchmark-1.1.0)

add_executable(bm main.cpp
  SplitString.cpp
  critical_section.cpp
  returning_vector.cpp
  thread_safe_queue.cpp)

target_link_libraries(
  bm
  benchmark CppStudy
 )
