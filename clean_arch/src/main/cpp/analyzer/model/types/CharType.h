#pragma once

#include "EulType.h"

struct CharType : public EulType {
  const unsigned char size;
  CharType(unsigned char size) : size(size) {}
};
