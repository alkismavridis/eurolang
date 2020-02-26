#pragma once

#include<string>

#include "EulValue.h"

/**
    This class represents a string token.
*/
struct StringNode : public EulValue {
    const std::string value;

    StringNode(const std::string& buf, AstLocation location);
};
