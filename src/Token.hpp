#pragma once
#include <string>

enum class TokenType {
    Number,
    Identifier,
    Operator,
    LParen,
    RParen,
    Comma,
    End,
    Unknown
};

struct Token {
    TokenType type;
    std::string text;
    double value = 0.0;
    size_t pos = 0;

    Token() = default;
    Token(TokenType t, std::string s, size_t p)
        : type(t), text(s), pos(p) {}
};
