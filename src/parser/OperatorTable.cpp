#include "OperatorTable.hpp"

OperatorTable::OperatorTable() {
    _binary["+"] = {"+", 1, Assoc::LEFT, 2, false};
    _binary["-"] = {"-", 1, Assoc::LEFT, 2, false};
    _binary["*"] = {"*", 2, Assoc::LEFT, 2, false};
    _binary["/"] = {"/", 2, Assoc::LEFT, 2, false};

    _unary["+"] = {"+", 4, Assoc::RIGHT, 1, true};
    _unary["-"] = {"-", 4, Assoc::RIGHT, 1, true};
}

const OperatorInfo* OperatorTable::findBinary(const std::string& symbol) const {
    auto it = _binary.find(symbol);
    return (it != _binary.end()) ? &it->second : nullptr;
}

const OperatorInfo* OperatorTable::findUnary(const std::string& symbol) const {
    auto it = _unary.find(symbol);
    return (it != _unary.end()) ? &it->second : nullptr;
}
