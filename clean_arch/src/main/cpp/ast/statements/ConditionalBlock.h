#pragma once

#include <memory>
#include <list>


#include "ast/AstNode.h"
#include "ast/values/EulValue.h"
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
