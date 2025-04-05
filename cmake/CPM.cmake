file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.8/CPM.cmake
  ${CMAKE_BINARY_DIR}/_deps/CPM.cmake
  EXPECTED_MD5 f2c95720301a3fb2ee34488f0ab5c87f
)
include(${CMAKE_BINARY_DIR}/_deps/CPM.cmake)
