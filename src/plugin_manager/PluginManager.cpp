#include "PluginManager.hpp"
#include "../platform/WinDynamicLibrary.hpp"
#include <filesystem>
#include <iostream>
#include <cstdlib>

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

bool PluginManager::_compileIfNeeded(const std::string& src, const std::string& out) {
    try {
        if (fs::exists(out)) {
            auto tSrc = fs::last_write_time(src);
            auto tOut = fs::last_write_time(out);
            if (tOut >= tSrc)
                return false;
        }

        std::string name = fs::path(src).stem().string();
        std::cout << "Compiling plugin: " << name << "..." << std::endl;

        std::string cmd =
            "g++ -std=c++20 -shared -fPIC -O2 "
            "-I./src/plugins "
            "-o \"" + out + "\" \"" + src + "\"";

        int res = std::system(cmd.c_str());
        if (res == 0) {
            std::cout << "Built " << out << std::endl;
            return true;
        } else {
            std::cerr << "Failed to build " << name << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception compiling plugin: " << e.what() << std::endl;
        return false;
    }
}

void PluginManager::buildPluginsFromSource(const std::string& srcDir, const std::string& outDir) {
    if (!fs::exists(srcDir)) return;

    for (const auto& entry : fs::directory_iterator(srcDir)) {
        if (entry.path().extension() == ".cpp") {
            std::string src = entry.path().string();
            std::string name = entry.path().stem().string();
            std::string out = outDir + "/" + name + ".dll";
            _compileIfNeeded(src, out);
        }
    }
}