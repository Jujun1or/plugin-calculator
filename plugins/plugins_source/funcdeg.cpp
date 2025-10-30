#define _USE_MATH_DEFINES
#include <cmath>
#include "../../src/plugin_manager/PluginAPI.hpp"

static double deg_func(const double* args, int argc, bool* ok, const char** err) {
    if (argc != 1) {
        *ok = false;
        *err = "deg() takes exactly 1 argument";
        return 0.0;
    }
    *ok = true;
    return args[0] * M_PI / 180.0;
}

extern "C" __declspec(dllexport) bool get_function(FunctionSpec* out) {
    out->name = "deg";
    out->arity = 1;
    out->func = deg_func;
    return true;
}
