#pragma once
#include <string>

enum class Assoc { LEFT, RIGHT };

struct OperatorInfo {
    std::string symbol;
    int precedence;
    Assoc assoc;
    int arity;
    bool isUnary;
};
