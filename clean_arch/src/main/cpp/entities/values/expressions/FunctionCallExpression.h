#pragma once

#include <vector>

#include "../EulValue.h"

struct FunctionCallExpression : public EulValue {
  const EulValue* func;
  std::vector<EulValue*> params;

  FunctionCallExpression(EulValue* func);
  FunctionCallExpression* addParam(EulValue* param);
};
