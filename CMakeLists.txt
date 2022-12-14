cmake_minimum_required(VERSION 3.14)

project(result)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive- /W4 /w14640 /EHsc")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wnon-virtual-dtor -Wpedantic")
endif()

include(cmake/CPM.cmake)
cpmaddpackage("gh:TheLartians/Format.cmake@1.7.3")

add_library(result INTERFACE)
target_include_directories(result INTERFACE include)

if(BUILD_TESTING AND CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  enable_testing()

  cpmaddpackage("gh:catchorg/Catch2@3.2.0")
  include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")

  if(NOT MSVC)
    # set coverage flags (not supported in MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")
  endif()

  add_executable(result_test test/err_test.cpp test/result_test.cpp test/result_of_test.cpp)
  target_link_libraries(result_test PRIVATE result Catch2::Catch2WithMain)
  catch_discover_tests(result_test)
endif()
