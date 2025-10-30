#include <cmath>
#include "../../src/plugin_manager/PluginAPI.hpp"

static double sin_func(const double* args, int argc, bool* ok, const char** err) {
    if (argc != 1) {
        *ok = false;
        *err = "sin() takes exactly 1 argument";
        return 0.0;
    }
    *ok = true;
    return std::sin(args[0]);
}

extern "C" __declspec(dllexport) bool get_function(FunctionSpec* out) {
    out->name = "sin";
    out->arity = 1;
    out->func = sin_func;
    return true;
}
