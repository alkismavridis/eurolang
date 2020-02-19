#pragma once

#include "../EulValue.h"

struct BooleanNode : public EulValue {
  bool const value;

  BooleanNode(const bool val);
};
