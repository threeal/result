file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.2/CPM.cmake
  ${CMAKE_BINARY_DIR}/_deps/CPM.cmake
  EXPECTED_MD5 4d51aa9dab6104fad39c5b7a692d5e1c
)
include(${CMAKE_BINARY_DIR}/_deps/CPM.cmake)
