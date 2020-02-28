#pragma once

#include <list>
#include <vector>
#include <memory>

#include "ast/values/SymbolNameNode.h"
#include "TypeNode.h"
#include "StatementType.h"
#include "EulStatement.h"
#include "VarDeclarationStatement.h"


/**
 A statement that consist of a single expression.
 For example an assignment statement or a function call.
*/
struct FunctionDeclarationStatement : public EulStatement {
  const std::unique_ptr<const SymbolNameNode> name;
  const std::unique_ptr<const TypeNode> returnType; //nullptr means a void function
  const std::vector<std::unique_ptr<const VarDeclarationStatement>> parameters;
  const std::list<std::unique_ptr<const EulStatement>> statements;


  FunctionDeclarationStatement(
    std::unique_ptr<const SymbolNameNode> name,
    std::unique_ptr<const TypeNode> returnType,
    std::vector<std::unique_ptr<const VarDeclarationStatement>> parameters,
    std::list<std::unique_ptr<const EulStatement>> statements,
    AstLocation location
  ) :
    EulStatement(location),
    name(move(name)),
    parameters(move(parameters)),
    statements(move(statements)),
    returnType(move(returnType)) {}

  StatementType getType() { return StatementType::FUNC_DECLARATION; }
};
