cmake_minimum_required(VERSION 3.14)

project(result)

set(CMAKE_CXX_STANDARD 17)

include(cmake/CPM.cmake)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR AND BUILD_TESTING)
  cpmaddpackage(gh:threeal/CheckWarning.cmake@2.1.1)
  include(${CheckWarning_SOURCE_DIR}/cmake/CheckWarning.cmake)
  add_check_warning()
endif()

cpmaddpackage(
  NAME error
  GIT_TAG f9b39f8
  GITHUB_REPOSITORY threeal/cpp
  SOURCE_SUBDIR error)

add_library(result INTERFACE)
target_include_directories(result INTERFACE include)
target_link_libraries(result INTERFACE error)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  cpmaddpackage(
    GITHUB_REPOSITORY TheLartians/Format.cmake
    VERSION 1.8.0
    OPTIONS "FORMAT_SKIP_CMAKE ON"
  )

  if(BUILD_TESTING)
    enable_testing()

    cpmaddpackage(gh:catchorg/Catch2@3.5.4)
    include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")

    if(NOT MSVC)
      # set coverage flags (not supported in MSVC)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")
    endif()

    add_executable(result_test test/result_test.cpp)
    target_link_libraries(result_test PRIVATE result Catch2::Catch2WithMain)
    catch_discover_tests(result_test)
  endif()
endif()
