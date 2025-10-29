#include "WinDynamicLibrary.hpp"
#include <iostream>

WinDynamicLibrary::WinDynamicLibrary(const std::string& path) {
    handle = LoadLibraryA(path.c_str());
    if (!handle) {
        std::cerr << "Failed to load DLL: " << path << std::endl;
    }
}

WinDynamicLibrary::~WinDynamicLibrary() {
    if (handle) {
        FreeLibrary(handle);
    }
}

void* WinDynamicLibrary::getSymbol(const std::string& name) const {
    if (!handle) return nullptr;
    return reinterpret_cast<void*>(GetProcAddress(handle, name.c_str()));
}
