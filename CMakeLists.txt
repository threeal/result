cmake_minimum_required(VERSION 3.21)

project(result)

set(CMAKE_CXX_STANDARD 17)

option(RESULT_ENABLE_TESTS "Enable test targets.")

include(cmake/CPM.cmake)

if(PROJECT_IS_TOP_LEVEL AND RESULT_ENABLE_TESTS)
  cpmaddpackage(gh:threeal/CheckWarning.cmake@3.2.0)
  add_check_warning(TREAT_WARNINGS_AS_ERRORS)
endif()

cpmaddpackage(gh:threeal/errors-cpp@1.0.0)

add_library(result INTERFACE)
target_include_directories(result INTERFACE include)
target_link_libraries(result INTERFACE errors)

if(PROJECT_IS_TOP_LEVEL)
  cpmaddpackage(
    GITHUB_REPOSITORY TheLartians/Format.cmake
    VERSION 1.8.0
    OPTIONS "FORMAT_SKIP_CMAKE ON"
  )

  if(RESULT_ENABLE_TESTS)
    enable_testing()

    cpmaddpackage(gh:catchorg/Catch2@3.10.0)
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
