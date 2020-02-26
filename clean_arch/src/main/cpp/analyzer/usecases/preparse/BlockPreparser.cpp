#include "ast/statements/StatementType.h"
#include "ast/statements/FunctionDeclarationStatement.h"

#include "BlockPreparser.h"


BlockPreparser::BlockPreparser(AstMetadata* meta) : meta(meta) {
  this->statementHandlers[StatementType::FUNC_DECLARATION] = [=](EulStatement* stmt) -> void {
    this->parseFunctionDeclaration(static_cast<FunctionDeclarationStatement*>(stmt));
  };
}


void BlockPreparser::parseFunctionDeclaration(FunctionDeclarationStatement* stmt) {
}
