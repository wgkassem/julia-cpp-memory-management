# Find GTest or fetch if cannot be found on system
#find_package(GTest QUIET)
if(NOT GTest_FOUND)
  message(STATUS "GTest not found, fetching from GitHub")
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP 1
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)
else()
  message(STATUS "GTest found, using system version")
  message(STATUS "GTest include dir: ${GTEST_INCLUDE_DIRS}")
  message(STATUS "GTest libraries: ${GTEST_LIBRARIES}")
endif()
