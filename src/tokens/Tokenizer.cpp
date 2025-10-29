#include "Tokenizer.hpp"
#include <cctype>

Tokenizer::Tokenizer(const std::string& input) : _input(input) {}

char Tokenizer::current() const {
    return _pos < _input.size() ? _input[_pos] : '\0';
}

bool Tokenizer::eof() const {
    return _pos >= _input.size();
}

void Tokenizer::skipSpaces() {
    while (!eof() && std::isspace(static_cast<unsigned char>(_input[_pos])))
        ++_pos;
}

Token Tokenizer::next() {
    skipSpaces();
    if (eof()) return Token(TokenType::End, "", _pos);

    char c = current();

    if (std::isdigit(c) || (c == '.' && std::isdigit(_input[_pos + 1]))) {
        size_t start = _pos;
        bool dot = false;
        while (!eof() && (std::isdigit(current()) || current() == '.')) {
            if (current() == '.') {
                if (dot) break;
                dot = true;
            }
            ++_pos;
        }
        std::string text = _input.substr(start, _pos - start);
        return Token(TokenType::Number, text, start);
    }
    if (std::isalpha(c) || c == '_') {
        size_t start = _pos;
        while (!eof() && (std::isalnum(current()) || current() == '_'))
            ++_pos;
        std::string text = _input.substr(start, _pos - start);
        return Token(TokenType::Identifier, text, start);
    }

    ++_pos;
    switch (c) {
        case '+': case '-': case '*': case '/':
            return Token(TokenType::Operator, std::string(1, c), _pos - 1);
        case '(':
            return Token(TokenType::LParen, "(", _pos - 1);
        case ')':
            return Token(TokenType::RParen, ")", _pos - 1);
        case ',':
            return Token(TokenType::Comma, ",", _pos - 1);
        default:
            return Token(TokenType::Unknown, std::string(1, c), _pos - 1);
    }
}

Token Tokenizer::peek() const {
    return Token(); 
}
