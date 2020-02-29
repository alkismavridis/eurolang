#pragma once

#include "ast/AstNode.h"

struct EulValue : public AstNode {
	virtual ~EulValue() {}

	EulValue(AstLocation location);
};
