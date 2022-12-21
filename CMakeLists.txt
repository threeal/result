cmake_minimum_required(VERSION 3.14)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic")

project(result)

include(cmake/CPM.cmake)
cpmaddpackage("gh:TheLartians/Format.cmake@1.7.3")

add_library(result INTERFACE)
target_include_directories(result INTERFACE include)

if(BUILD_TESTING)
  enable_testing()

  find_package(Catch2 REQUIRED)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")
  add_executable(result_test test/result_test.cpp test/result_or_test.cpp)
  target_link_libraries(result_test PRIVATE result Catch2::Catch2WithMain)
  catch_discover_tests(result_test)
endif()
