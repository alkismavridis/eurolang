#pragma once

#include <unordered_map>
#include <functional>
#include <memory>

#include "model/ast/statements/StatementType.h"
#include "model/ast/statements/EulStatement.h"
#include "model/ast/statements/FunctionDeclarationStatement.h"

#include "model/ast_metadata/AstMetadata.h"

struct BlockParser {
	static void parseBlock(std::list<std::unique_ptr<const EulStatement>>& statements, AstMetadata* meta);
	static void preDeclareTypes(std::list<std::unique_ptr<const EulStatement>>& statements, AstMetadata* meta);

	static void declareTypeFor(const FunctionDeclarationStatement* stmt, AstMetadata* meta);
};
