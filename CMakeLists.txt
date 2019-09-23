# Support version 3.6 and above, but use policy settings up to 3.14.
# 3.6 is needed because of IMPORTED_TARGET in pkg_check_modules().
cmake_minimum_required(VERSION 3.6...3.14)
# Ranges are supported from 3.12, set policy to current for < 3.12.
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(identiconpp
  VERSION 0.7.1
  LANGUAGES CXX)
# DESCRIPTION was introduced in version 3.9.
if(NOT (${CMAKE_VERSION} VERSION_LESS 3.9))
  set(PROJECT_DESCRIPTION
    "Library to generate identicons for C++.")
endif()

option(WITH_TESTS "Enable Tests" NO)
option(BUILD_SHARED_LIBS "Build shared libraries." YES)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(DEBUG_CXXFLAGS
  "-Wall"
  "-Wextra"
  "-Wpedantic"
  "-ftrapv"
  "-fsanitize=undefined"
  "-g"
  "-Og"
  "-fno-omit-frame-pointer")
set(DEBUG_LDFLAGS
  "-fsanitize=undefined")
add_compile_options("$<$<CONFIG:Debug>:${DEBUG_CXXFLAGS}>")
# add_link_options was introduced in version 3.13.
if(${CMAKE_VERSION} VERSION_LESS 3.13)
  set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${DEBUG_LDFLAGS}")
else()
  add_link_options("$<$<CONFIG:Debug>:${DEBUG_LDFLAGS}>")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG=1)
endif()

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(cmake)
add_subdirectory(pkg-config)

if(WITH_TESTS)
  add_subdirectory(tests)
endif()

include(packages.CMakeLists.txt)
