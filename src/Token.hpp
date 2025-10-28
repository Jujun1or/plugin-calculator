#pragma once
#include <string>

enum class TokenType {
    Number,
    Operator,
    Unknown,
    End
};

struct Token {
    TokenType type;
    std::string text;
    size_t pos = 0;

    Token() = default;
    Token(TokenType t, std::string s, size_t p)
        : type(t), text(s), pos(p) {}
};
