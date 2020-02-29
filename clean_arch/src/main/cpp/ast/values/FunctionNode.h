#pragma once

#include <memory>
#include <vector>
#include <list>

#include "ast/statements/TypeNode.h"
#include "ast/statements/EulStatement.h"
#include "ast/statements/VarDeclarationStatement.h"
#include "ast/statements/ScopeRoot.h"

struct FunctionNode : public EulValue, public ScopeRoot {
	const std::unique_ptr<const TypeNode> returnType; //nullptr means a void function
	const std::vector<std::unique_ptr<const VarDeclarationStatement>> parameters;
	const std::list<std::unique_ptr<const EulStatement>> statements;

	FunctionNode(
		std::unique_ptr<const TypeNode> returnType,
		std::vector<std::unique_ptr<const VarDeclarationStatement>> parameters,
		std::list<std::unique_ptr<const EulStatement>> statements,
		AstLocation location
	) :
		EulValue(location),
		returnType(move(returnType)),
		parameters(move(parameters)),
		statements(move(statements)) {}
};
