#pragma once

#include "../EulValue.h"

struct CharNode : public EulValue {
  unsigned long int const value;
  unsigned char const size; //in bytes


  CharNode(unsigned long int value, unsigned char size);
};
