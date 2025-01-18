file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.5/CPM.cmake
  ${CMAKE_BINARY_DIR}/_deps/CPM.cmake
  EXPECTED_MD5 19cbb284c7b175d239670d47dd9d0e9e
)
include(${CMAKE_BINARY_DIR}/_deps/CPM.cmake)
