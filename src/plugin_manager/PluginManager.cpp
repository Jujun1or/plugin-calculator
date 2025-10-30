#include "PluginManager.hpp"
#include "../platform/WinDynamicLibrary.hpp"
#include <filesystem>
#include <iostream>


namespace fs = std::filesystem;

bool PluginManager::loadPlugins(const std::string& dir) {
    if (!fs::exists(dir)) {
        std::cerr << "Plugins directory not found: " << dir << std::endl;
        return false;
    }

    int count = 0;
    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.path().extension() == ".dll") {
            auto lib = std::make_unique<WinDynamicLibrary>(entry.path().string());
            if (!lib->isLoaded()) continue;

            auto sym = reinterpret_cast<bool(*)(FunctionSpec*)>(lib->getSymbol("get_function"));
            if (!sym) {
                std::cerr << "DLL missing get_function: " << entry.path().filename() << std::endl;
                continue;
            }

            FunctionSpec spec{};
            if (!sym(&spec)) {
                std::cerr << "Plugin failed to initialize: " << entry.path().filename() << std::endl;
                continue;
            }

            PluginFunction f;
            f.name = spec.name ? spec.name : "";
            f.arity = spec.arity;
            f.func = spec.func;

            if (f.name.empty() || !f.func) {
                std::cerr << "Invalid function in: " << entry.path().filename() << std::endl;
                continue;
            }

            functions[f.name] = f;
            libs.push_back(std::move(lib));
            ++count;
        }
    }

    if (count == 0) {
        std::cout << "No valid plugins found.\n";
        return false;
    }

    return true;
}

bool PluginManager::hasFunction(const std::string& name) const {
    return functions.find(name) != functions.end();
}

const PluginFunction* PluginManager::getFunction(const std::string& name) const {
    auto it = functions.find(name);
    return (it != functions.end()) ? &it->second : nullptr;
}

void PluginManager::printLoaded() const {
    if (functions.empty()) {
        std::cout << "No plugins loaded.\n";
        return;
    }

    std::cout << "Loaded functions:\n";
    for (const auto& [name, f] : functions) {
        std::cout << "  - " << name << " (" << f.arity << " args)\n";
    }
}
