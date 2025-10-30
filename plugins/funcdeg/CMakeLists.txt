cmake_minimum_required(VERSION 3.15)
project(funcdeg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(funcdeg SHARED funcdeg.cpp)
set_target_properties(funcdeg PROPERTIES
    OUTPUT_NAME "funcdeg"
    PREFIX ""
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
)
