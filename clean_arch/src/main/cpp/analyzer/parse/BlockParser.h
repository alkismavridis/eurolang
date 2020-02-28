#pragma once

#include <unordered_map>
#include <functional>

#include "ast/statements/StatementType.h"
#include "ast/statements/EulStatement.h"
#include "ast/statements/FunctionDeclarationStatement.h"

#include "analyzer/model/meta/AstMetadata.h"

struct BlockParser {
  void parseBlock(std::list<std::unique_ptr<const EulStatement>>& statements);
  void declareTypes(std::list<std::unique_ptr<const EulStatement>>& statements);
};
