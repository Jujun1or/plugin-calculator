#pragma once
#include <string>
#include "Tokenizer.hpp"
#include "OperatorTable.hpp"
#include "Rpn.hpp"

class Parser {
public:
    explicit Parser(const std::string& expr);
    bool parse();
    void printRpn() const;

    const RpnProgram& getRpn() const { return rpn; }

private:
    Tokenizer tokenizer;
    OperatorTable ops;
    RpnProgram rpn;

    bool toRpn(); // Shunting-yard
};