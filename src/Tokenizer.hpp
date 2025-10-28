#pragma once
#include <string>
#include "Token.hpp"

class Tokenizer {
public:
    explicit Tokenizer(const std::string& input);
    Token next();
    Token peek() const;

private:
    std::string _input;
    size_t _pos = 0;

    void skipSpaces();
    char current() const;
    bool eof() const;
};
