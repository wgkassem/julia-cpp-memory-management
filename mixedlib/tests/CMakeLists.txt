message(STATUS "Building tests")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GoogleTest REQUIRED)
include(GoogleTest)

# Tests for common target
add_executable(test_common test_common.cpp)
target_include_directories(test_common PUBLIC
  ${CMAKE_SOURCE_DIR}/include
  ${GTEST_INCLUDE_DIRS}
  ${Julia_INCLUDE_DIRS}
)
add_definitions(-DJULIA_ENABLE_THREADING)
target_link_libraries(test_common PRIVATE ${Julia_LIBRARY} gtest gtest_main)

# Tests for trapz target 
add_executable(test_trapz test_trapz.cpp)
target_include_directories(test_trapz PUBLIC
  "include"
  ${GTEST_INCLUDE_DIRS}
)
add_definitions(-DJULIA_ENABLE_THREADING)
target_link_libraries(test_trapz PRIVATE trapz gtest gtest_main)

# Tests for shared_trapz target 
add_executable(test_shared_trapz test_shared_trapz.cpp)
target_include_directories(test_shared_trapz PUBLIC
  "include"
  ${GTEST_INCLUDE_DIRS}
)
add_definitions(-DJULIA_ENABLE_THREADING)
target_link_libraries(test_shared_trapz PRIVATE shared_trapz gtest gtest_main)


gtest_discover_tests(test_common)
gtest_discover_tests(test_trapz)
gtest_discover_tests(test_shared_trapz)
