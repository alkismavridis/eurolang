#pragma once

#include "EulValue.h"


/**
    This class represents an int token. Ints in EUL have a size, and can be signed or unsigned.
*/
struct IntNode : public EulValue {
    const unsigned long int value;
    const unsigned char size; //in bits
    const bool isUnsigned;

    IntNode(unsigned long int value, unsigned char size, bool isUnsigned, AstLocation location);
};
