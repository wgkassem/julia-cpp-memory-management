cmake_minimum_required(VERSION 3.10)
project(memory_management)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(cpp_pointers cpp_pointers.cpp)
target_include_directories(cpp_pointers PUBLIC
  "include"
)

