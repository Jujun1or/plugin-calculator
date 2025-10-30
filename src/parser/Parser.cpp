#include "Parser.hpp"

Parser::Parser(const std::string& expr, const PluginManager& pm)
    : tokenizer(expr), plugins(pm) {}

bool Parser::parse() {
    return toRpn();
}

bool Parser::toRpn() {
    std::stack<std::string> opStack;
    bool expectOperand = true;

    Token t;
    while ((t = tokenizer.next()).type != TokenType::End) {
        if (t.type == TokenType::Number) {
            rpn.add({RpnItemType::NUMBER, t.text});
            expectOperand = false;
        }
        else if (t.type == TokenType::Identifier) {
            if (plugins.hasFunction(t.text)) {
                Token next = tokenizer.next();
                if (next.type != TokenType::LParen) {
                    std::cerr << "Expected '(' after function name " << t.text << "\n";
                    return false;
                }
                opStack.push(t.text);
                opStack.push("(");
                expectOperand = true;
            } else {
                std::cerr << "Unknown identifier: " << t.text << "\n";
                return false;
            }
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
            opStack.pop();

            if (!opStack.empty()) {
                std::string func = opStack.top();
                if (plugins.hasFunction(func)) {
                    rpn.add({RpnItemType::FUNCTION_CALL, func});
                    opStack.pop();
                }
            }
            expectOperand = false;
        }
        else if (t.type == TokenType::Operator) {
            if (t.text == "-" && expectOperand) {
                const OperatorInfo* uMinus = ops.findUnary("-");
                if (!uMinus) {
                    std::cerr << "Operator table missing unary '-'\n";
                    return false;
                }
                opStack.push("u-");
                continue;
            }

            const OperatorInfo* o1 = ops.findBinary(t.text);
            if (!o1) {
                std::cerr << "Unknown operator: " << t.text << "\n";
                return false;
            }

            while (!opStack.empty()) {
                const OperatorInfo* o2 = ops.findBinary(opStack.top());
                if (!o2) break;
                if ((o1->assoc == Assoc::LEFT && o1->precedence <= o2->precedence) ||
                    (o1->assoc == Assoc::RIGHT && o1->precedence < o2->precedence)) {
                    rpn.add({RpnItemType::BINARY_OP, opStack.top()});
                    opStack.pop();
                } else break;
            }
            opStack.push(t.text);
            expectOperand = true;
        }
        else {
            std::cerr << "Unexpected token: " << t.text << "\n";
            return false;
        }
    }

    while (!opStack.empty()) {
        if (opStack.top() == "(") {
            std::cerr << "Mismatched parentheses\n";
            return false;
        }
        std::string op = opStack.top();
        opStack.pop();
        if (op == "u-")
            rpn.add({RpnItemType::UNARY_OP, op});
        else
            rpn.add({RpnItemType::BINARY_OP, op});
    }

    return true;
}

void Parser::printRpn() const {
    rpn.print();
}
