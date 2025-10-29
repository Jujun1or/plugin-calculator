cmake_minimum_required(VERSION 3.15)
project(Calculator LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(calc
    src/app/main.cpp
    src/tokens/Tokenizer.cpp
    src/parser/OperatorTable.cpp
    src/parser/Parser.cpp
    src/rpn/Rpn.cpp
    src/eval/Evaluator.cpp
    src/platform/WinDynamicLibrary.cpp
    src/plugin_manager/PluginManager.cpp
)



if (WIN32)
    set_target_properties(calc PROPERTIES
        WIN32_EXECUTABLE FALSE
        OUTPUT_NAME "calc"
    )
endif()

add_subdirectory(plugins)
