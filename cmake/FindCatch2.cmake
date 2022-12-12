if(Catch2_FOUND)
  return()
endif()

include(CPM)
cpmaddpackage("gh:catchorg/Catch2@3.2.0")

include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")
