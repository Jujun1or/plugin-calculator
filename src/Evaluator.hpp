#pragma once
#include "Rpn.hpp"
#include <string>
#include <unordered_map>

class Evaluator {
public:
    double evaluate(const RpnProgram& program, bool& ok, std::string& err) const;

private:
    double applyOperator(const std::string& op, double a, double b, bool& ok, std::string& err) const;
};
