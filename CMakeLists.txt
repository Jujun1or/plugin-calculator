cmake_minimum_required(VERSION 3.15)
project(Calculator LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(calc
    src/main.cpp
    src/Tokenizer.cpp
    src/Parser.cpp
    src/OperatorTable.cpp
    src/Rpn.cpp
    src/Evaluator.cpp
)

if (WIN32)
    set_target_properties(calc PROPERTIES
        WIN32_EXECUTABLE FALSE
        OUTPUT_NAME "calc"
    )
endif()

add_subdirectory(plugins)
