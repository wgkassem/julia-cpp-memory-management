cmake_minimum_required(VERSION 3.10)
project(mixedlib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)  # C++14 for google test
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Julia
find_package(Julia REQUIRED)
find_package(mymemory REQUIRED)
# echo mymemory_INCLUDE_DIRS
message(STATUS "mymemory include dirs: ${mymemory_INCLUDE_DIRECTORIES}")

# add target embed_example that embeds Julia

add_library(trapz SHARED
  src/trapz.cpp
)
# echo ${JULIA_INCLUDE_DIRS}
message(STATUS "Julia include dirs: ${Julia_INCLUDE_DIRS}")
target_include_directories(trapz PUBLIC include ${Julia_INCLUDE_DIRS})
target_link_libraries(trapz
  ${Julia_LIBRARY}
)

add_library(shared_trapz SHARED
  src/shared_trapz.cpp
)
target_include_directories(shared_trapz PUBLIC include ${Julia_INCLUDE_DIRS})
target_link_libraries(shared_trapz
  ${Julia_LIBRARY}
  mymemory::mymemory
)

if (BUILD_TESTING)
  enable_testing()
 add_subdirectory(tests)
endif()
