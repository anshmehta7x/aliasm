cmake_minimum_required(VERSION 3.16)
project(aliasm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

file(GLOB_RECURSE UI_SOURCES src/ui/*.cpp)
file(GLOB_RECURSE UTIL_SOURCES src/util/*.cpp)

add_executable(aliasm
    src/main.cpp
    ${UI_SOURCES}
    ${UTIL_SOURCES}
)

target_include_directories(aliasm PRIVATE
    ${GTKMM_INCLUDE_DIRS}
    src/ui
    src/util
)

target_link_libraries(aliasm PRIVATE ${GTKMM_LIBRARIES})
target_compile_options(aliasm PRIVATE ${GTKMM_CFLAGS_OTHER})
