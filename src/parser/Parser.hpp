#pragma once
#include <string>
#include <stack>
#include <iostream>
#include "../tokens/Tokenizer.hpp"
#include "OperatorTable.hpp"
#include "../rpn/Rpn.hpp"
#include "../plugin_manager/PluginManager.hpp"

class Parser {
public:
    explicit Parser(const std::string& expr, const PluginManager& pm);
    bool parse();
    void printRpn() const;

    const RpnProgram& getRpn() const { return rpn; }

private:
    Tokenizer tokenizer;
    OperatorTable ops;
    RpnProgram rpn;
    const PluginManager& plugins; 

    bool toRpn(); // Shunting-yard
};