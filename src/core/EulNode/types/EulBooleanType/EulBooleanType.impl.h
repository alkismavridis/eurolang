#pragma once


//region LIFE CYCLE
//endregion


//region CORE FUNCTIONS
EulTypeEnum EulBooleanType::getTypeEnum() { return EulTypeEnum::BOOLEAN_TYPE; }
//endregion


//region CODE GENERATION
llvm::Value* EulBooleanType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    if (sourceType->getTypeEnum() == EulTypeEnum::BOOLEAN_TYPE) return sourceValue;
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "Cannot cast a non boolean value to boolean.");
}

llvm::Type* EulBooleanType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::Type::getInt1Ty(ctx->context);
}
//endregion


//region SERIALIZATION
void EulBooleanType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulBooleanType\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
