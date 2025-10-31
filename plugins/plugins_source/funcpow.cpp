#include <cmath>
#include "../../src/plugin_manager/PluginAPI.hpp"

static double pow_func(const double* args, int argc, bool* ok, const char** err) {
    if (argc != 2) {
        *ok = false;
        *err = "pow() requires 2 arguments";
        return 0.0;
    }

    double base = args[0];
    double exp = args[1];

    if (base < 0 && std::fmod(exp, 1.0) != 0.0) {
        *ok = false;
        *err = "pow() error (negative base with non-integer exponent)";
        return 0.0;
    }

    errno = 0;
    double result = std::pow(base, exp);

    if (errno == EDOM || errno == ERANGE || std::isnan(result) || std::isinf(result)) {
        *ok = false;
        *err = "pow() overflow or invalid operation";
        return 0.0;
    }

    *ok = true;
    return result;
}

extern "C" __declspec(dllexport) bool get_function(FunctionSpec* out) {
    out->name = "pow";
    out->arity = 2;
    out->func = pow_func;
    return true;
}
