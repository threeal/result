file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.1/CPM.cmake
  ${CMAKE_BINARY_DIR}/_deps/CPM.cmake
  EXPECTED_MD5 a5467d77aa63a1197ea4e1644623acb7
)
include(${CMAKE_BINARY_DIR}/_deps/CPM.cmake)
