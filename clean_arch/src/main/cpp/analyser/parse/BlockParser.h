#pragma once

#include <unordered_map>
#include <functional>
#include <memory>

#include "ast/statements/StatementType.h"
#include "ast/statements/EulStatement.h"
#include "ast/statements/FunctionDeclarationStatement.h"

#include "analyser/model/meta/AstMetadata.h"

struct BlockParser {
	static void parseBlock(std::list<std::unique_ptr<const EulStatement>>& statements, AstMetadata* meta);
	static void preDeclareTypes(std::list<std::unique_ptr<const EulStatement>>& statements, AstMetadata* meta);

	static void declareTypeFor(const FunctionDeclarationStatement* stmt, AstMetadata* meta);
};
