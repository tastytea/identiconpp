cmake_minimum_required (VERSION 3.2)
project(identiconpp
        VERSION 0.3.5
        LANGUAGES CXX
)

include(GNUInstallDirs)
find_package(PkgConfig REQUIRED)
pkg_check_modules(MAGICPP REQUIRED Magick++)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

string(REPLACE ";" " " MAGICPP_CFLAGS_STRING "${MAGICPP_CFLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MAGICPP_CFLAGS_STRING}")
set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic -Wextra -g -Og -fno-omit-frame-pointer")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG=1)
endif()

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR})
include_directories(${MAGICPP_INCLUDE_DIRS})

link_directories(${MAGICPP_LIBRARY_DIRS})

file(GLOB sources src/*.cpp)
add_library(${CMAKE_PROJECT_NAME} SHARED "${sources}")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION ${${CMAKE_PROJECT_NAME}_VERSION_MAJOR})
target_link_libraries(${CMAKE_PROJECT_NAME} "${MAGICPP_LDFLAGS}")

add_executable(example "example.cpp")
target_link_libraries(example ${CMAKE_PROJECT_NAME})

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES src/${CMAKE_PROJECT_NAME}.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})

include(packages.CMakeLists.txt)
include(tests.CMakeLists.txt)
