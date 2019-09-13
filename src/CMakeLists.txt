include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Magick++ REQUIRED IMPORTED_TARGET Magick++)

file(GLOB sources *.cpp)
add_library(${PROJECT_NAME} ${sources} ${PROJECT_NAME}.hpp)
target_link_libraries(${PROJECT_NAME} PkgConfig::Magick++)
set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR})

install(TARGETS ${PROJECT_NAME}
  EXPORT "${PROJECT_NAME}Targets"
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${PROJECT_NAME}.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
