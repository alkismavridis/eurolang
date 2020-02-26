#pragma once
#include "ast/AstNode.h"
#include "StatementType.h"

struct EulStatement : public AstNode {
  EulStatement(AstLocation location);
  virtual ~EulStatement() {}

  virtual StatementType getType() { return StatementType::UNKNOWN; }
};
