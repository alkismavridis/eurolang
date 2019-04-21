#pragma once



//region LIFE CYCLE
EulSuffixExp::EulSuffixExp(std::shared_ptr<ValueNode> exp, EulOperator* oper) {
    this->exp = exp;
    this->oper = oper;
}
//endregion



//region CORE FUNCTIONS
EulExpressionType EulSuffixExp::getExpressionType() { return EulExpressionType::SUFFIX_EXP; }
//endregion



//region CODE GENERATION
llvm::Value* EulSuffixExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    std::cout << "EulSuffixExp::generateValue TODO NOT IMPLEMENTED" << std::endl;
    return nullptr; //TODO
}
//endregion



//region SERIALIZING
void EulSuffixExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulSuffixExp\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"exp\":";
    this->exp->toJson(out, tabs+1);
    out << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"oper\":" << this->oper->getOperatorText() << "," << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
