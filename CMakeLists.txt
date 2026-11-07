cmake_minimum_required(VERSION 3.20)
project(
    GLnoBS
    DESCRIPTION "OpenGL, No Bullshitting"
    VERSION 0.1.0
    LANGUAGES CXX
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

if (GLPP_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()