#pragma once
#include <string>
#include <vector>
#include "Token.hpp"
#include "Tokenizer.hpp"

class Parser {
public:
    explicit Parser(const std::string& expr);
    bool parse();
    void debugPrint() const;

private:
    Tokenizer tokenizer;
    std::vector<Token> tokens;
};
