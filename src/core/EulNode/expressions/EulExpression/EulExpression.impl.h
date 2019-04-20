#pragma once

EulExpressionType EulExpression::getExpressionType() {
  return EulExpressionType::UNKNOWN_EXP;
}

std::shared_ptr<EulType> EulExpression::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
  return this->compileTimeType;
}

bool EulExpression::isSymbolId() { return false; }

EulNodeType EulExpression::getNodeType() { return EulNodeType::EXPRESSION; }
