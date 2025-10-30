cmake_minimum_required(VERSION 3.15)
project(Plugins LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

file(GLOB_RECURSE PLUGIN_SOURCES "*.cpp")

foreach(SRC ${PLUGIN_SOURCES})
    get_filename_component(PLUGIN_NAME ${SRC} NAME_WE)

    add_library(${PLUGIN_NAME} SHARED ${SRC})
    set_target_properties(${PLUGIN_NAME} PROPERTIES
        OUTPUT_NAME ${PLUGIN_NAME}
        PREFIX ""
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
    )

    message(STATUS "Configured plugin: ${PLUGIN_NAME}")
endforeach()
