#pragma once
#include <string>
#include <vector>

enum class RpnItemType {
    NUMBER,
    UNARY_OP,
    BINARY_OP,
    FUNCTION_CALL
};

struct RpnItem {
    RpnItemType type;
    std::string text;
};

class RpnProgram {
public:
    void add(const RpnItem& item);
    void print() const;

    const std::vector<RpnItem>& getItems() const { return _code; }
    bool empty() const { return _code.empty(); }
    RpnItemType lastType() const;

private:
    std::vector<RpnItem> _code;
};
