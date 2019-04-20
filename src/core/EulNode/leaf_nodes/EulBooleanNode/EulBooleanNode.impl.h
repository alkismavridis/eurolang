#pragma once


//region LIFE CYCLE
EulBooleanNode::EulBooleanNode(bool value) {
    this->value = value;
}
//endregion



//region CORE FUNCTIONS
EulNodeType EulBooleanNode::getNodeType() { return EulNodeType::BOOLEAN; }
bool EulBooleanNode::isSymbolId() { return false; }
//endregion



//region CODE GENERATION
llvm::Value* EulBooleanNode::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    return llvm::ConstantInt::get(ctx->context, llvm::APInt(1, this->value? 1 : 0, true));
}

std::shared_ptr<EulType> EulBooleanNode::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    return ctx->compiler->program.nativeTypes.booleanType;
}
//endregion



//region SERIALIZATION
void EulBooleanNode::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulBooleanNode\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    if (this->value) out << "\"value\": true" << std::endl;
    else out << "\"value\": false" << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
