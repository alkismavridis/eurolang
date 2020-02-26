#pragma once

#include <memory>
#include "ast/values/EulValue.h"

struct ArrayAccessExpression : public EulValue {
  const std::unique_ptr<const EulValue> arr;
  const std::unique_ptr<const EulValue> index;


  ArrayAccessExpression(std::unique_ptr<const EulValue> arr, std::unique_ptr<const EulValue> index, AstLocation location);
};
