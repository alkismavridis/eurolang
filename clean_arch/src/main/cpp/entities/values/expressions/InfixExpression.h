#pragma once

#include "../EulValue.h"

class EulOperator;
struct InfixExpression : public EulValue {
  const EulValue* left;
  const EulOperator* oper;
  const EulValue* right;

  InfixExpression(EulValue* left, EulOperator* oper, EulValue* right);
};
