#pragma once


//region LIFE CYCLE
EulIntegerType::EulIntegerType(unsigned char size, bool isUnsigned) {
    this->size = size;
    this->isUnsigned = isUnsigned;
}



//endregion



//region CORE FUNCTIONS
EulTypeEnum EulIntegerType::getTypeEnum() { return EulTypeEnum::INT_TYPE; }
//endregion



//region CODE GENERATION
llvm::Value* EulIntegerType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    //NOTE at the moment only int to int castings are allowed.

    //1. Check that the source type is indeed an integer
    if (sourceType->getTypeEnum() != EulTypeEnum::INT_TYPE) throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED only ints can be casted to ints.");

    //2. If the target value has less bits than the source, trunk the value
    auto targetLlvmType = this->getLlvmType(ctx);
    if (this->isUnsigned) return ctx->builder.CreateZExtOrTrunc(sourceValue, targetLlvmType);
    else return ctx->builder.CreateSExtOrTrunc(sourceValue, targetLlvmType);
}

llvm::Type* EulIntegerType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, this->size);
}
//endregion



//region SERIALIZATION
void EulIntegerType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulIntegerType\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"size\":" << (int)this->size << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"isUnsigned\":" << this->isUnsigned << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
