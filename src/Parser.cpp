#include "Parser.hpp"
#include <stack>
#include <iostream>

Parser::Parser(const std::string& expr)
    : tokenizer(expr) {}

bool Parser::parse() {
    return toRpn();
}

bool Parser::toRpn() {
    std::stack<std::string> opStack;
    Token t = tokenizer.next();
    Token prev;
    bool expectOperand = true;

    while (t.type != TokenType::End) {
        if (t.type == TokenType::Number) {
            rpn.add({RpnItemType::NUMBER, t.text});
            expectOperand = false;
        }
        else if (t.type == TokenType::Operator) {
            const OperatorInfo* opInfo = nullptr;
            if (expectOperand)
                opInfo = ops.findUnary(t.text);
            else
                opInfo = ops.findBinary(t.text);

            if (!opInfo) {
                std::cerr << "Unknown operator: " << t.text << "\n";
                return false;
            }

            while (!opStack.empty()) {
                const OperatorInfo* topInfo = ops.findBinary(opStack.top());
                if (!topInfo) break;

                bool cond = (opInfo->assoc == Assoc::LEFT && opInfo->precedence <= topInfo->precedence)
                         || (opInfo->assoc == Assoc::RIGHT && opInfo->precedence < topInfo->precedence);

                if (cond) {
                    rpn.add({RpnItemType::BINARY_OP, opStack.top()});
                    opStack.pop();
                } else break;
            }

            opStack.push(t.text);
            expectOperand = true;
        }
        else if (t.type == TokenType::LParen) {
            opStack.push("(");
            expectOperand = true;
        }
        else if (t.type == TokenType::RParen) {
            while (!opStack.empty() && opStack.top() != "(") {
                rpn.add({RpnItemType::BINARY_OP, opStack.top()});
                opStack.pop();
            }
            if (opStack.empty()) {
                std::cerr << "Mismatched parentheses\n";
                return false;
            }
            opStack.pop(); // remove '('
            expectOperand = false;
        }
        t = tokenizer.next();
    }

    while (!opStack.empty()) {
        if (opStack.top() == "(") {
            std::cerr << "Mismatched parentheses\n";
            return false;
        }
        rpn.add({RpnItemType::BINARY_OP, opStack.top()});
        opStack.pop();
    }
    return true;
}

void Parser::printRpn() const {
    rpn.print();
}

