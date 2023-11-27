# print that we are building the test suite 
add_executable(mymemory_test_suite "test_mymemory.cpp")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GoogleTest REQUIRED)

# print GTest include dirs 
message(STATUS "GTest source dirs: ${googletest_SOURCE_DIR}")

target_include_directories(mymemory_test_suite PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(mymemory_test_suite PRIVATE mymemory gtest gtest_main)
gtest_discover_tests(mymemory_test_suite)

install(TARGETS mymemory_test_suite RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

