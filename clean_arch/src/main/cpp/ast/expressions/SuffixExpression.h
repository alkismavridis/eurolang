#pragma once

#include <memory>

#include "ast/values/EulValue.h"
#include "OperatorNode.h"

struct SuffixExpression : public EulValue {
  const std::unique_ptr<const EulValue> left;
  const std::unique_ptr<const OperatorNode> oper;

  SuffixExpression(std::unique_ptr<const EulValue> left, std::unique_ptr<const OperatorNode> oper, AstLocation location);
};
