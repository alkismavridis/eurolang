#pragma once

//region LIFE CYCLE
EulIntNode::EulIntNode(unsigned long int value, unsigned char size, bool isUnsigned) {
    this->value = value;
    this->size = size;
    this->isUnsigned = isUnsigned;
}

EulIntNode::EulIntNode(char* text) {
    this->value = strtoul(text, &text, 10);		//setup value
    if (*text) { //setup signed or unsigned flag
        this->isUnsigned = (*text) == 'u';
        text++;
    }
    else this->isUnsigned = false; //default is signed

    if (*text) this->size = strtoul(text, &text, 10);	//setup size, if any
    else this->size = EUL_LANG_DEFAULT_INT_SIZE;
}
//endregion



//region CORE FUNCTIONS
EulNodeType EulIntNode::getNodeType() { return EulNodeType::INT; }
bool EulIntNode::isSymbolId() { return false; }
//endregion



//region CODE GENERATION
llvm::Value* EulIntNode::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    switch(this->size) {
        case 8:
        case 16:
        case 32:
        case 64: return llvm::ConstantInt::get(ctx->context, llvm::APInt(this->size, this->value, !this->isUnsigned));
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid integer size: " + std::to_string(this->size)+". Please use one of 8, 16, 32, 64.");
    }
}


std::shared_ptr<EulType> EulIntNode::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    switch(this->size) {
        case 8: return this->isUnsigned? ctx->compiler->program.nativeTypes.uint8Type : ctx->compiler->program.nativeTypes.int8Type;
        case 16: return this->isUnsigned? ctx->compiler->program.nativeTypes.uint16Type : ctx->compiler->program.nativeTypes.int16Type;
        case 32: return this->isUnsigned? ctx->compiler->program.nativeTypes.uint32Type : ctx->compiler->program.nativeTypes.int32Type;
        case 64: return this->isUnsigned? ctx->compiler->program.nativeTypes.uint64Type : ctx->compiler->program.nativeTypes.int64Type;
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid integer size: " + std::to_string(this->size)+". Please use one of 8, 16, 32, 64.");
    }
}
//endregion



//region SERIALIZING
void EulIntNode::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulIntNode\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"value\":" <<  this->value << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"size\":" <<  (int) this->size << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"isUnsigned\": " <<  (int) this->isUnsigned << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
