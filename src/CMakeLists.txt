find_package(PkgConfig REQUIRED)
pkg_check_modules(MAGICPP REQUIRED Magick++)

include_directories(${MAGICPP_INCLUDE_DIRS})

link_directories(${MAGICPP_LIBRARY_DIRS})

file(GLOB sources *.cpp)
add_library(${PROJECT_NAME} SHARED ${sources})
target_link_libraries(${PROJECT_NAME} ${MAGICPP_LIBRARIES})
target_compile_options(${PROJECT_NAME} PUBLIC ${MAGICPP_CFLAGS})
set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES src/${CMAKE_PROJECT_NAME}.hpp src/${CMAKE_PROJECT_NAME}_c.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
