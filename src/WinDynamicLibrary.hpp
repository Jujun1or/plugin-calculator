#pragma once
#include "IDynamicLibrary.hpp"
#include <windows.h>
#include <string>

class WinDynamicLibrary : public IDynamicLibrary {
public:
    explicit WinDynamicLibrary(const std::string& path);
    ~WinDynamicLibrary() override;

    void* getSymbol(const std::string& name) const override;
    bool isLoaded() const { return handle != nullptr; }

private:
    HMODULE handle = nullptr;
};
