#pragma once

#include "../EulValue.h"

/**
    This class represents a float token. Floats in EUL have a size.
*/
struct FloatNode : public EulValue {
    double const value;
    unsigned char const size; //in bytes


    FloatNode(double value, unsigned char size);
};
