cmake_minimum_required(VERSION 3.31.6)
project(
  UmbraLog
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

# -------------------------
# Library target
# -------------------------
add_library(umbra_log STATIC src/log.cpp src/logger.cpp)

# -------------------------
# Test executable
# -------------------------
add_executable(test_UmbraLog test/test_main.cpp)

target_link_libraries(test_UmbraLog PRIVATE umbra_log)

# -------------------------
# Include directories
# -------------------------
target_include_directories(
  umbra_log PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                   $<INSTALL_INTERFACE:include>)

# -------------------------
# Shared build define (optional)
# -------------------------
if(BUILD_SHARED_LIBS)
  target_compile_definitions(umbra_log PRIVATE UMBRA_BUILD_DLL)
endif()

# -------------------------
# Compiler features + PCH
# -------------------------
target_compile_features(umbra_log PRIVATE cxx_std_20)
target_precompile_headers(umbra_log PRIVATE include/pch/log-pch.h)

# -------------------------
# Installation
# -------------------------
include(GNUInstallDirs)

install(
  TARGETS umbra_log
  EXPORT UmbraLogTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
  EXPORT UmbraLogTargets
  FILE UmbraLogTargets.cmake
  NAMESPACE Umbra::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UmbraLog)
