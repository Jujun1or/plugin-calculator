#include <iostream>
#include "../parser/Parser.hpp"
#include "../eval/Evaluator.hpp"
#include "../plugin_manager/PluginManager.hpp"

int main() {
    PluginManager plugins;
    plugins.loadPlugins("./plugins");
    plugins.printLoaded();

    std::cout << "Enter expression: ";
    std::string expr;
    std::getline(std::cin, expr);

    Parser parser(expr);
    if (!parser.parse()) {
        std::cerr << "Parse error.\n";
        return 1;
    }

    parser.printRpn();

    bool ok = false;
    std::string err;
    Evaluator eval;
    double result = eval.evaluate(parser.getRpn(), ok, err);

    if (!ok) {
        std::cerr << "Error: " << err << "\n";
        return 1;
    }

    std::cout << "Result: " << result << "\n";
    return 0;
}
