#pragma once

#include <list>
#include <memory>

#include "StatementType.h"
#include "EulStatement.h"
#include "ConditionalBlock.h"

/**
 A statement that consist of a single expression.
 For example an assignment statement or a function call.
*/
struct IfStatement : public EulStatement {
  const std::unique_ptr<const ConditionalBlock> ifBlock;
  std::list<std::unique_ptr<const ConditionalBlock>> elseIfBlocks;
  const std::unique_ptr<const ConditionalBlock> elseBlock;

  IfStatement(std::unique_ptr<const ConditionalBlock> ifBlock, AstLocation location);
  IfStatement(std::unique_ptr<const ConditionalBlock> ifBlock, std::unique_ptr<const ConditionalBlock> elseBlock, AstLocation location);

  StatementType getType() { return StatementType::IF; }
};
