#pragma once

#include "EulValue.h"

/**
    This class represents a float token. Floats in EUL have a size.
*/
struct FloatNode : public EulValue {
    const double value;
    const unsigned char size; //in bytes


    FloatNode(double value, unsigned char size, AstLocation location);
};
