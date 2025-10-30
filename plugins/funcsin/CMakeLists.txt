cmake_minimum_required(VERSION 3.15)
project(funcsin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(funcsin SHARED funcsin.cpp)
set_target_properties(funcsin PROPERTIES
    OUTPUT_NAME "funcsin"
    PREFIX ""
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
)
