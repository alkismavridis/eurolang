#pragma once

#include <memory>

#include "ast/values/FunctionNode.h"


/**
 A statement that consist of a single expression.
 For example an assignment statement or a function call.
*/
struct FunctionDeclarationStatement : public EulStatement {
	const std::unique_ptr<const SymbolNameNode> name;
	const std::unique_ptr<const FunctionNode> value;


	FunctionDeclarationStatement(
		std::unique_ptr<const SymbolNameNode> name,
		std::unique_ptr<const FunctionNode> value,
		AstLocation location
	) :
		EulStatement(location),
		name(move(name)),
		value(move(value))	{}

	StatementType getType() const { return StatementType::FUNC_DECLARATION; }
};
