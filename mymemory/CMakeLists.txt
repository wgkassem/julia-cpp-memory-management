cmake_minimum_required(VERSION 3.12)
project(mymemory VERSION 1.0.0)

# Include GNUInstallDirs module
include(GNUInstallDirs)

# Define the target (headers-only)
add_library(mymemory INTERFACE)
target_include_directories(mymemory INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Specify the version of the library
set_target_properties(mymemory PROPERTIES
    VERSION ${PROJECT_VERSION}
)

# Install the headers
install(DIRECTORY include/mymemory
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install the CMake configuration files
install(TARGETS mymemory
    EXPORT mymemoryConfig
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT mymemoryConfig
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mymemory
)

# Create a package configuration file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/mymemoryConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mymemoryConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mymemory
)

# Export the targets to a script
install(EXPORT mymemoryConfig
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mymemory
    NAMESPACE mymemory::
)

# Install the exported targets
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mymemoryConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mymemory
)

# Define the test target (using GoogleTest)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

