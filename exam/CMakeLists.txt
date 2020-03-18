include_directories(
  ${PROJECT_SOURCE_DIR}/third_party/Catch2/single_include
  ${PROJECT_BINARY_DIR}/include
)

add_executable(
  Tester
  Tester.cpp
  ast.cpp
  tcmalloc.cpp
)

target_link_libraries(
  Tester
  clang
  tcmalloc
)
