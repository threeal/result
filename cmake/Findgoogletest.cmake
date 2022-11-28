if(googletest_FOUND)
  return()
endif()

include(CPM)

CPMAddPackage(
  NAME googletest
  GITHUB_REPOSITORY google/googletest
  GIT_TAG release-1.12.1
)

include(GoogleTest)
