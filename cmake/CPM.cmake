file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.42.0/CPM.cmake
  ${CMAKE_BINARY_DIR}/_deps/CPM.cmake
  EXPECTED_MD5 e5facfa5d8d61f058d5a6e3e5391a3b7
)
include(${CMAKE_BINARY_DIR}/_deps/CPM.cmake)
