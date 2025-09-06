cmake_minimum_required(VERSION 3.20)
project(iofsw
    VERSION 1.0.0
    DESCRIPTION "Modern C++ header-only library"
    HOMEPAGE_URL "https://github.com/pooriayousefi/iofsw"
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Header-only library target
add_library(iofsw INTERFACE)
target_include_directories(iofsw INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Set interface properties
target_compile_features(iofsw INTERFACE cxx_std_20)

# Platform-specific compile definitions
if(WIN32)
    target_compile_definitions(iofsw INTERFACE _WIN32_WINNT=0x0601)
endif()

# Installation
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS iofsw
    EXPORT iofswTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/iofsw.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    OPTIONAL
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/iofsw.ixx
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    OPTIONAL
)

# Export targets
install(EXPORT iofswTargets
    FILE iofswTargets.cmake
    NAMESPACE iofsw::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/iofsw
)

# Create package config
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/iofswConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/iofswConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/iofsw
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/iofswConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/iofswConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/iofswConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/iofsw
)

# Configuration summary
message(STATUS "iofsw Configuration Summary:")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Platform: ${CMAKE_SYSTEM_NAME}")
