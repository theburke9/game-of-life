cmake_minimum_required(VERSION 3.16)
project(GameOfLife)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(core)
add_subdirectory(game)
add_subdirectory(render)

add_executable(GameOfLife WIN32 main.c)
target_link_libraries(GameOfLife PRIVATE game core render SDL3::SDL3)
