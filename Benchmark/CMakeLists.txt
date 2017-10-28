include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/vendor/benchmark/include
  )

add_executable(bm main.cpp
  SplitString.cpp
  critical_section.cpp
  returning_vector.cpp
  thread_safe_queue.cpp)

target_link_libraries(
  bm
  benchmark CppStudy
 )
