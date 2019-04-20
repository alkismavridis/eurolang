#pragma once


//region LIFE CYCLE
EulStringType::EulStringType() {}
//endregion


//region CORE FUNCTIONS
EulTypeEnum EulStringType::getTypeEnum() { return EulTypeEnum::STRING_TYPE; }
//endregion



//region CODE GENERATION
llvm::Value* EulStringType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    if (sourceType->getTypeEnum() != EulTypeEnum::STRING_TYPE)
        throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED Only string can be casted to string.");

    return sourceValue;
}

llvm::Type* EulStringType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, 8)->getPointerTo();
}
//endregion



//region SERIALIZATION
void EulStringType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulStringType\"" << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
