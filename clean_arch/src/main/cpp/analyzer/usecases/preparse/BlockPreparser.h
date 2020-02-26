#pragma once

#include <unordered_map>
#include <functional>

#include "ast/statements/StatementType.h"
#include "ast/statements/EulStatement.h"
#include "ast/statements/FunctionDeclarationStatement.h"

#include "analyzer/model/meta/AstMetadata.h"



struct BlockPreparser {
  AstMetadata* const meta;
  std::unordered_map<StatementType, std::function<void(EulStatement*)>> statementHandlers;

  BlockPreparser(AstMetadata* meta);

private:
  void parseFunctionDeclaration(FunctionDeclarationStatement* stmt);
};
