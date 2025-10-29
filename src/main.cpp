#include <iostream>
#include "Parser.hpp"

int main() {
    std::cout << "Enter expression: ";
    std::string expr;
    std::getline(std::cin, expr);

    Parser parser(expr);
    if (parser.parse()) {
        parser.printRpn();
    } else {
        std::cerr << "Parse error.\n";
    }

    return 0;
}
