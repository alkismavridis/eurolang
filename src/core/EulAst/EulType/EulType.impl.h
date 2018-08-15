#pragma once


//region BASE CLASS
EulAstType EulType::getAstType() { return EUL_TYPE; }

bool EulType::isEulType(EulToken* tok) {
    if (tok->getType() != AST) return false;
    if ( ((EulAst*)tok)->getAstType() != EUL_TYPE) return false;
    return true;
}

llvm::Type* EulType::getLlvmType(EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulType::getLlvmType was called.");
}

EulTypeEnum EulType::getTypeEnum() { return VOID_TYPE; }
//endregion



//region INT TYPE
EulIntegerType::EulIntegerType(unsigned char size, bool isUnsigned) {
    this->size = size;
    this->isUnsigned = isUnsigned;
}

void EulIntegerType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulIntegerType\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"size\":" << this->size << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"isUnsigned\":" << this->isUnsigned << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

llvm::Type* EulIntegerType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, this->size);
}

EulTypeEnum EulIntegerType::getTypeEnum() { return INT_TYPE; }
//endregion


//region CHAR TYPE
EulCharType::EulCharType(unsigned char size) {
    this->size = size;
}

void EulCharType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulCharType\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"size\":" << this->size << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

llvm::Type* EulCharType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, this->size);
}

EulTypeEnum EulCharType::getTypeEnum() { return CHAR_TYPE; }
//endregion





//region STRING TYPE
EulStringType::EulStringType() {}

void EulStringType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulStringType\"" << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

llvm::Type* EulStringType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, 8)->getPointerTo();
}

EulTypeEnum EulStringType::getTypeEnum() { return STRING_TYPE; }
//endregion


//region NAMED TYPES
EulNamedType::EulNamedType(const std::string& name) {
    this->name = name;
}

void EulNamedType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulType\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"name\":" << this->name << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

llvm::Type* EulNamedType::getLlvmType(EulCodeGenContext* ctx) {
    return ctx->module->getTypeByName(this->name);
}

EulTypeEnum EulNamedType::getTypeEnum() { return NAMED_TYPE; }
//endregion