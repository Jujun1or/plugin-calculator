#pragma once

typedef double (*plugin_func_t)(const double* args, int argc, bool* ok, const char** err);

struct FunctionSpec {
    const char* name; // имя 
    int         arity; // количество аргументов
    plugin_func_t func; // поинтер на функцию
};

extern "C" __declspec(dllexport) bool get_function(FunctionSpec* out);
