#include "Parser.hpp"
#include <iostream>

Parser::Parser(const std::string& expr)
    : tokenizer(expr) {}

bool Parser::parse() {
    tokens.clear();
    Token t;
    do {
        t = tokenizer.next();
        tokens.push_back(t);
    } while (t.type != TokenType::End);

    return true;
}

void Parser::debugPrint() const {
    for (const auto& t : tokens) {
        std::cout << "Token: " << t.text << " (" << static_cast<int>(t.type) << ")\n";
    }
}
