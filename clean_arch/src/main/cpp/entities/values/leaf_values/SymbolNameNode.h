#pragma once

#include<string>

#include "../EulValue.h"

/**
    This class represents an ID token, like a variable name or a method.
*/
struct SymbolNameNode : public EulValue {
    std::string const name;

    SymbolNameNode(const std::string& buf);
};
