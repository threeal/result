cmake_minimum_required(VERSION 3.14)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
set(CMAKE_CXX_STANDARD 17)

project(result)

add_library(result INTERFACE)
target_include_directories(result INTERFACE include)

if(BUILD_TESTING)
  enable_testing()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -coverage")

  find_package(Catch2 REQUIRED)

  add_executable(result_test test/result_test.cpp test/result_or_test.cpp)
  target_link_libraries(result_test PRIVATE result Catch2::Catch2WithMain)
  catch_discover_tests(result_test)
endif()
