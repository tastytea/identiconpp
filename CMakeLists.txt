cmake_minimum_required (VERSION 3.2)
project(identiconpp
  VERSION 0.6.1
  LANGUAGES CXX)

option(WITH_TESTS "Enable Tests" NO)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG
  "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wpedantic -ftrapv \
-fsanitize=undefined -g -Og -fno-omit-frame-pointer")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG=1)
endif()

include(GNUInstallDirs)

install(FILES README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})

add_subdirectory(src)

configure_file("${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.pc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc" @ONLY)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")

if(WITH_TESTS)
  add_subdirectory(tests)
endif()

include(packages.CMakeLists.txt)
