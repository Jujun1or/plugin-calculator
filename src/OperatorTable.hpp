#pragma once
#include <string>
#include <unordered_map>
#include "OperatorInfo.hpp"

class OperatorTable {
public:
    OperatorTable();

    const OperatorInfo* findBinary(const std::string& symbol) const;
    const OperatorInfo* findUnary(const std::string& symbol) const;

private:
    std::unordered_map<std::string, OperatorInfo> _binary;
    std::unordered_map<std::string, OperatorInfo> _unary;
};
