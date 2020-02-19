#pragma once

#include<string>

#include "../EulValue.h"

/**
    This class represents a string token.
*/
struct StringNode : public EulValue {
    std::string const value;

    StringNode(const std::string& buf);
};
