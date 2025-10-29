#include "Rpn.hpp"
#include <iostream>

void RpnProgram::add(const RpnItem& item) {
    _code.push_back(item);
}

void RpnProgram::print() const {
    std::cout << "RPN: ";
    for (const auto& i : _code)
        std::cout << i.text << " ";
    std::cout << "\n";
}
