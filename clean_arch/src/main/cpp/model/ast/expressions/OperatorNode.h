#pragma once

#include "EulOperator.h"
#include "model/ast/AstNode.h"

struct OperatorNode : public AstNode {
	const EulOperator* const eulOperator;

	OperatorNode(const EulOperator* eulOperator, AstLocation location);
};
