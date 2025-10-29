#pragma once
#include <string>

class IDynamicLibrary {
public:
    virtual ~IDynamicLibrary() = default;
    virtual void* getSymbol(const std::string& name) const = 0;
};
