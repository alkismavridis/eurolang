#pragma once


//region LIFE CYCLE
//endregion


//region CORE FUNCTIONS
EulTypeEnum EulVoidType::getTypeEnum() { return EulTypeEnum::VOID_TYPE; }
//endregion


//region CODE GENERATION
llvm::Value* EulVoidType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    if (sourceValue != nullptr)
        throw EulError(EulErrorType::NOT_IMPLEMENTED, "Cannot cast a value to void.");
    return nullptr;
}

llvm::Type* EulVoidType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::Type::getVoidTy(ctx->context);
}
//endregion


//region SERIALIZATION
void EulVoidType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulVoidType\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
