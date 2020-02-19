#pragma once

#include "../values/EulValue.h"
#include "EulStatement.h"

/**
 A statement that consist of a single expression.
 For example an assignment statement or a function call.
*/
struct ExpressionStatement : public EulStatement {
  const EulValue* expression;

  ExpressionStatement(EulValue* expression);

};
