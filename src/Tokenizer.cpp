#include "Tokenizer.hpp"

Tokenizer::Tokenizer(const std::string& input)
    : _input(input) {}

Token Tokenizer::next() {
    return Token(TokenType::End, "", _pos);
}

Token Tokenizer::peek() {
    return Token(TokenType::End, "", _pos);
}
