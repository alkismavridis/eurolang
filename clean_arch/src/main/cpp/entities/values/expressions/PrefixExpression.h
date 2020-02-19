#pragma once

#include "../EulValue.h"

class EulOperator;
struct PrefixExpression : public EulValue {
  const EulOperator* oper;
  const EulValue* right;

  PrefixExpression(EulOperator* oper, EulValue* right);
};
