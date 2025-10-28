#pragma once
#include <string>
#include "Token.hpp"

class Tokenizer {
public:
    explicit Tokenizer(const std::string& input);

    Token next();
    Token peek();

private:
    std::string _input;
    size_t _pos = 0;
};
