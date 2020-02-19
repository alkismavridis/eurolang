#pragma once

#include "../EulValue.h"


/**
    This class represents an int token. Ints in EUL have a size, and can be signed or unsigned.
*/
struct IntNode : public EulValue {
    unsigned long int const value;
    unsigned char const size; //in bits
    bool const isUnsigned;

    IntNode(unsigned long int value, unsigned char size, bool isUnsigned);
};
