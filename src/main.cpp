#include <iostream>
#include "Tokenizer.hpp"

int main() {
    std::string expr;
    std::cout << "Enter expression: ";
    std::getline(std::cin, expr);

    Tokenizer tokenizer(expr);
    Token t = tokenizer.next();
    std::cout << "First token type: " << static_cast<int>(t.type) << "\n";

    return 0;
}
