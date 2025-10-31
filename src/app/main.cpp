#include <iostream>
#include <filesystem>
#include <cstdlib>
#include "../parser/Parser.hpp"
#include "../eval/Evaluator.hpp"
#include "../plugin_manager/PluginManager.hpp"


int main() {
    PluginManager plugins;

    plugins.buildPluginsFromSource("plugins/plugins_source", "plugins");
    plugins.loadPlugins("plugins");
    plugins.printLoaded();

    Evaluator eval(plugins);
    std::cout << "\nType 'exit' to quit.\n";

    while (true) {
        plugins.buildPluginsFromSource("plugins/plugins_source", "plugins");

        plugins.loadPlugins("plugins");

        std::cout << "\nEnter expression: ";
        std::string expr;
        std::getline(std::cin, expr);

        if (expr == "exit" || expr == "quit")
            break;

        if (expr.empty())
            continue;

        Parser parser(expr, plugins);
        if (!parser.parse()) {
            std::cerr << "Parse error.\n";
            continue;
        }

        parser.printRpn();

        bool ok = false;
        std::string err;
        double result = eval.evaluate(parser.getRpn(), ok, err);

        if (!ok) {
            std::cerr << "Error: " << err << "\n";
        } else {
            std::cout << "Result: " << result << "\n";
        }
    }

    std::cout << "\nGoodbye!\n";
    return 0;
}