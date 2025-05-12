cmake_minimum_required(VERSION 3.16)
project(aliasm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

add_executable(aliasm src/main.cpp)
target_include_directories(aliasm PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(aliasm PRIVATE ${GTKMM_LIBRARIES})
target_compile_options(aliasm PRIVATE ${GTKMM_CFLAGS_OTHER})
