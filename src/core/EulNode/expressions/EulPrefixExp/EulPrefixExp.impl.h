#pragma once


//region LIFE CYCLE
EulPrefixExp::EulPrefixExp(EulOperator* oper, std::shared_ptr<ValueNode> exp) {
    this->exp = exp;
    this->oper = oper;
}
//endregion



//region CORE FUNCTIONS
EulExpressionType EulPrefixExp::getExpressionType() { return EulExpressionType::PREFIX_EXP; }
//endregion



//region CODE GENERATION
llvm::Value* EulPrefixExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {


  if (this->oper->isAssignment()) {
    //return this->generateAssignment(ctx, flags);
    std::cout << "TODO EulPrefixExp::generateValue isAssignment NOT IMPLEMENTED\n\n" << std::endl;
    return nullptr;
  }

  //1. Calculate the values of the two operands. This will generate their types, too
  llvm::Value* expValue = this->exp->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);
  if (!expValue) return nullptr;

  //2. Perform and return the operation
  return this->oper->performPrefix(
      expValue,
      this->exp->getEulType(ctx, 0),
      &this->compileTimeType,
      ctx
  );
}
//endregion



//region SERIALIZING
void EulPrefixExp::toJson(std::ostream& out, int tabs) {
   out << "{" << std::endl;
   for (int i=tabs; i>=0; --i) out << "\t";
   out << "\"type\":\"EulPrefixExp\"," << std::endl;

   for (int i=tabs; i>=0; --i) out << "\t";
   out << "\"oper\":" << this->oper->getOperatorText() << "," << std::endl;

   for (int i=tabs; i>=0; --i) out << "\t";
   out << "\"exp\":";
   this->exp->toJson(out, tabs+1);
   out << std::endl;

   for (int i=tabs-1; i>=0; --i) out << "\t";
   out << "}";
}
//endregion
