#pragma once

#include <memory>

#include "ast/values/EulValue.h"
#include "OperatorNode.h"

struct InfixExpression : public EulValue {
  const std::unique_ptr<const EulValue> left;
  const std::unique_ptr<const OperatorNode> oper;
  const std::unique_ptr<const EulValue> right;

  InfixExpression(std::unique_ptr<const EulValue> left, std::unique_ptr<const OperatorNode> oper, std::unique_ptr<const EulValue> right, AstLocation location);
};
