file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.0/CPM.cmake
  ${CMAKE_BINARY_DIR}/_deps/CPM.cmake
  EXPECTED_MD5 6c9866a0aa0f804a36fe8c3866fb8a2c
)
include(${CMAKE_BINARY_DIR}/_deps/CPM.cmake)
