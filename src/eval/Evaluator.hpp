#pragma once
#include "../rpn/Rpn.hpp"
#include <string>
#include <stack>
#include <vector>
#include "../plugin_manager/PluginManager.hpp"

class Evaluator {
public:
    Evaluator(const PluginManager& pm);
    double evaluate(const RpnProgram& program, bool& ok, std::string& err) const;

private:
    const PluginManager& plugins;
    double applyOperator(const std::string& op, double a, double b, bool& ok, std::string& err) const;
};
