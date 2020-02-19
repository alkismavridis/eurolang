#pragma once

#include "../EulValue.h"

class EulOperator;
struct SuffixExpression : public EulValue {
  const EulValue* left;
  const EulOperator* oper;

  SuffixExpression(EulValue* left, EulOperator* oper);
};
