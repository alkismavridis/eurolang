#pragma once

#include <memory>
#include <list>


#include "model/ast/AstNode.h"
#include "model/ast/values/EulValue.h"
#include "ScopeRoot.h"
#include "EulStatement.h"


struct ConditionalBlock : public AstNode, public ScopeRoot {
	const std::unique_ptr<const EulValue> condition;
	private: const std::list<std::unique_ptr<const EulStatement>> statements;

	public: ConditionalBlock(
		std::unique_ptr<const EulValue> condition,
		std::list<std::unique_ptr<const EulStatement>> statements,
		AstLocation location
	);
};
