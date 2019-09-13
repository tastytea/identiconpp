# You need to install identiconpp first so that CMake can find it.
find_package(identiconpp REQUIRED CONFIG)
add_executable(example example.cpp)
target_link_libraries(example PRIVATE identiconpp::identiconpp)
