#pragma once

#include <memory>
#include "ast/values/EulValue.h"
#include "StatementType.h"
#include "EulStatement.h"

/**
 A statement that consist of a single expression.
 For example an assignment statement or a function call.
*/
struct ExpressionStatement : public EulStatement {
  const std::unique_ptr<const EulValue> expression;

  ExpressionStatement(std::unique_ptr<const EulValue> expression, AstLocation location);
  StatementType getType() { return StatementType::EXPRESSION; }
};
