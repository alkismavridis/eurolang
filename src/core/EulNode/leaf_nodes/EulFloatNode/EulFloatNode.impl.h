#pragma once


//region LIFE CYCLE
EulFloatNode::EulFloatNode(double value, unsigned char size) {
    this->value = value;
    this->size = size;
}

EulFloatNode::EulFloatNode(char* text) {
    this->value = strtod(text, &text);
    if (*text == 'f') text++; //skip f character, if any

    if (*text) this->size = strtoul(text, &text, 10);
    else this->size = EUL_LANG_DEFAULT_FLOAT_SIZE;
}
//endregion



//region CORE FUNCTIONS
EulNodeType EulFloatNode::getNodeType() { return EulNodeType::FLOAT; }
bool EulFloatNode::isSymbolId() { return false; }
//endregion



//region CODE GENERATION
llvm::Value* EulFloatNode::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    auto llvmType = this->getEulType(ctx, 0)->getLlvmType(ctx);
    return llvm::ConstantFP::get(llvmType, this->value);
}

std::shared_ptr<EulType> EulFloatNode::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    switch(this->size) {
        case 32: return ctx->compiler->program.nativeTypes.float32Type;
        case 64: return ctx->compiler->program.nativeTypes.float64Type;
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid floating point size: " + std::to_string(this->size)+". Please use one of 32, 64.");
    }
}
//endregion



//region SERIALIZATION
void EulFloatNode::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulFloatNode\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"value\": " <<  this->value << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
