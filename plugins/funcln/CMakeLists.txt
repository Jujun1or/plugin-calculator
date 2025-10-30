cmake_minimum_required(VERSION 3.15)
project(funcln LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(funcln SHARED funcln.cpp)
set_target_properties(funcln PROPERTIES
    OUTPUT_NAME "funcln"
    PREFIX ""
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
)
