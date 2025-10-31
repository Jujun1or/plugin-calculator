#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include "PluginAPI.hpp"
#include "../platform/IDynamicLibrary.hpp"


struct PluginFunction {
    std::string name;
    int arity;
    plugin_func_t func;
};

class PluginManager {
public:
    bool loadPlugins(const std::string& dir);
    bool hasFunction(const std::string& name) const;
    const PluginFunction* getFunction(const std::string& name) const;
    void buildPluginsFromSource(const std::string& srcDir, const std::string& outDir);

    void printLoaded() const;

private:
    std::vector<std::unique_ptr<IDynamicLibrary>> libs;
    std::unordered_map<std::string, PluginFunction> functions;
    
    bool _compileIfNeeded(const std::string& src, const std::string& out);
};
