file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.39.0/CPM.cmake
  ${CMAKE_BINARY_DIR}/_deps/CPM.cmake
  EXPECTED_MD5 04eefa38baf672f7e8fcd09075122517
)
include(${CMAKE_BINARY_DIR}/_deps/CPM.cmake)
