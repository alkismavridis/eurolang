#pragma once

#include "model/ast/AstNode.h"

struct EulValue : public AstNode {
	virtual ~EulValue() {}

	EulValue(AstLocation location);
};
