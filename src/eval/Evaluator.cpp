#include "Evaluator.hpp"
#include <cmath>
#include <iostream>

Evaluator::Evaluator(const PluginManager& pm)
    : plugins(pm) {}

double Evaluator::evaluate(const RpnProgram& program, bool& ok, std::string& err) const {
    ok = true;
    err.clear();
    std::stack<double> st;

    for (const auto& item : program.getItems()) {
        if (item.type == RpnItemType::NUMBER) {
            try {
                st.push(std::stod(item.text));
            } catch (...) {
                ok = false;
                err = "Invalid number: " + item.text;
                return 0.0;
            }
        }
        else if (item.type == RpnItemType::BINARY_OP) {
            if (st.size() < 2) {
                ok = false;
                err = "Not enough operands for operator " + item.text;
                return 0.0;
            }
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();

            double result = applyOperator(item.text, a, b, ok, err);
            if (!ok) return 0.0;
            st.push(result);
        }
        else if (item.type == RpnItemType::UNARY_OP) {
            if (st.empty()) {
                ok = false;
                err = "Not enough operands for unary operator " + item.text;
                return 0.0;
            }
            double a = st.top(); st.pop();
            double result = (item.text == "-") ? -a : a;
            st.push(result);
        }
        else if (item.type == RpnItemType::FUNCTION_CALL) {
            const PluginFunction* f = plugins.getFunction(item.text);
            if (!f) {
                ok = false;
                err = "Unknown function: " + item.text;
                return 0.0;
            }

            if (st.size() < f->arity) {
                ok = false;
                err = "Not enough arguments for function " + item.text;
                return 0.0;
            }

            std::vector<double> args(f->arity);
            for (int i = f->arity - 1; i >= 0; --i) {
                args[i] = st.top();
                st.pop();
            }

            bool callOk = true;
            const char* errMsg = nullptr;
            double res = f->func(args.data(), f->arity, &callOk, &errMsg);
            if (!callOk) {
                ok = false;
                err = errMsg ? errMsg : "Plugin function error";
                return 0.0;
            }

            st.push(res);
        }
    }

    if (st.size() != 1) {
        ok = false;
        err = "Unexpected evaluation state: stack not empty";
        return 0.0;
    }

    return st.top();
}

double Evaluator::applyOperator(const std::string& op, double a, double b, bool& ok, std::string& err) const {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) {
            ok = false;
            err = "Division by zero";
            return 0.0;
        }
        return a / b;
    }

    ok = false;
    err = "Unknown operator: " + op;
    return 0.0;
}
