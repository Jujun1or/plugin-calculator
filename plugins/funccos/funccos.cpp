#include <cmath>
#include "../../src/plugin_manager/PluginAPI.hpp"

static double cos_func(const double* args, int argc, bool* ok, const char** err) {
    if (argc != 1) {
        *ok = false;
        *err = "cos() takes exactly 1 argument";
        return 0.0;
    }
    *ok = true;
    return std::cos(args[0]);
}

extern "C" __declspec(dllexport) bool get_function(FunctionSpec* out) {
    out->name = "cos";
    out->arity = 1;
    out->func = cos_func;
    return true;
}
