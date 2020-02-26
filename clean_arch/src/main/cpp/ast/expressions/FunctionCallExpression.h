#pragma once

#include <vector>
#include <memory>

#include "ast/values/EulValue.h"

struct FunctionCallExpression : public EulValue {
  const std::unique_ptr<const EulValue> func;
  std::vector<std::unique_ptr<const EulValue>> params;

  FunctionCallExpression(std::unique_ptr<const EulValue> func, AstLocation location);

  FunctionCallExpression* addParam(std::unique_ptr<const EulValue> param);
};
