file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.6/CPM.cmake
  ${CMAKE_BINARY_DIR}/_deps/CPM.cmake
  EXPECTED_MD5 576c10c1a0be88c4da589f94891ac466
)
include(${CMAKE_BINARY_DIR}/_deps/CPM.cmake)
