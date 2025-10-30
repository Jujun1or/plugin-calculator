#include <cmath>
#include "../../src/plugin_manager/PluginAPI.hpp"

static double ln_func(const double* args, int argc, bool* ok, const char** err) {
    if (argc != 1) {
        *ok = false;
        *err = "ln() takes exactly 1 argument";
        return 0.0;
    }
    if (args[0] <= 0) {
        *ok = false;
        *err = "ln() domain error (argument <= 0)";
        return 0.0;
    }
    *ok = true;
    return std::log(args[0]);
}

extern "C" __declspec(dllexport) bool get_function(FunctionSpec* out) {
    out->name = "ln";
    out->arity = 1;
    out->func = ln_func;
    return true;
}
