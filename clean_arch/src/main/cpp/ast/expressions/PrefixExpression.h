#pragma once

#include <memory>

#include "ast/values/EulValue.h"
#include "OperatorNode.h"

struct PrefixExpression : public EulValue {
	const std::unique_ptr<const OperatorNode> oper;
	const std::unique_ptr<const EulValue> right;

	PrefixExpression(std::unique_ptr<const OperatorNode> oper, std::unique_ptr<const EulValue> right, AstLocation location);
};
