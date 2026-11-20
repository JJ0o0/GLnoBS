cmake_minimum_required(VERSION 3.20)
project(
    GLnoBS
    DESCRIPTION "OpenGL, No Bullshitting"
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(GLPP_BUILD_TESTS "Build GL no BS tests" OFF)

add_library(glpp STATIC)
add_library(glpp::glpp ALIAS glpp)

target_sources(glpp
    PRIVATE
        src/diagnostics/log.cpp
        
        src/core/device.cpp
)

target_include_directories(glpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(glpp
    PRIVATE
        -Wall -Wextra
)

if (GLPP_BUILD_TESTS AND NOT TARGET glad::glad)
    add_subdirectory(tests/third_party/glad)
endif()

if(NOT TARGET glad::glad)
    message(FATAL_ERROR "'glad::glad' target not found! Define said target before 'add_subdirectory(GLnoBS).'")
endif()

target_link_libraries(glpp
    PRIVATE
        glad::glad
)

if (GLPP_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()