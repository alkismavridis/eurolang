#pragma once

#include<string>

#include "EulValue.h"

/**
    This class represents an ID token, like a variable name or a method.
*/
struct SymbolNameNode : public EulValue {
    const std::string name;

    SymbolNameNode(const std::string& buf, AstLocation location);
};
