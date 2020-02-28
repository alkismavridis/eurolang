#pragma once

#include <list>
#include <memory>

#include "ast/values/EulValue.h"
#include "StatementType.h"
#include "EulStatement.h"


/**
 A statement that consist of a single expression.
 For example an assignment statement or a function call.
*/
struct WhileStatement : public EulStatement {
  const std::unique_ptr<const EulValue> condition;
  const std::list<std::unique_ptr<const EulStatement>> statements;

  WhileStatement(
    std::unique_ptr<const EulValue> condition,
    std::list<std::unique_ptr<const EulStatement>> statements,
    AstLocation location
  ) :
    EulStatement(location),
    statements(move(statements)),
    condition(move(condition)) {}

  StatementType getType() { return StatementType::WHILE; }
};
