cmake_minimum_required(VERSION 3.15)
project(funccos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(funccos SHARED funccos.cpp)
set_target_properties(funccos PROPERTIES
    OUTPUT_NAME "funccos"
    PREFIX ""
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
)
