#pragma once
#include "model/ast/AstNode.h"
#include "StatementType.h"

struct EulStatement : public AstNode {
	EulStatement(AstLocation location);
	virtual ~EulStatement() {}

	virtual StatementType getType() const { return StatementType::UNKNOWN; }
};
