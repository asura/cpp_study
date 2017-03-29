include_directories(
  benchmark-1.1.0/include
  )

add_subdirectory(benchmark-1.1.0)

add_executable(bm main.cpp
  critical_section.cpp
  returning_vector.cpp)
target_link_libraries(bm benchmark)
