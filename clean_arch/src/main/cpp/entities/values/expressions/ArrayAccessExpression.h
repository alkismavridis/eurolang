#pragma once

#include "../EulValue.h"

struct ArrayAccessExpression : public EulValue {
  const EulValue* arr;
  const EulValue* index;

  ArrayAccessExpression(EulValue* arr, EulValue* index);
};
