#pragma once

#include "EulType.h"

struct FloatType : public EulType {
  const unsigned char size;

  FloatType(unsigned char size) :
    size(size)  {}
};
