#pragma once

#include <memory>

#include "model/ast/values/EulValue.h"
#include "model/ast/values/SymbolNameNode.h"
#include "StatementType.h"
#include "EulStatement.h"
#include "SymbolChangeType.h"


struct VarDeclarationStatement : public EulStatement {
	const SymbolChangeType changeType;
	const std::unique_ptr<const SymbolNameNode> name;
	const std::unique_ptr<const EulValue> value;


	VarDeclarationStatement(SymbolChangeType changeType, std::unique_ptr<const SymbolNameNode> name, AstLocation location);

	VarDeclarationStatement(
		SymbolChangeType changeType,
		std::unique_ptr<const SymbolNameNode> name,
		std::unique_ptr<const EulValue> value,
		AstLocation location
	);

	StatementType getType() const { return StatementType::VAR_DECLARATION; }
};
