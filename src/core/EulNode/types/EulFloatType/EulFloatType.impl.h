#pragma once


//region LIFE CYCLE
EulFloatType::EulFloatType(unsigned char size) {
    this->size = size;
}
//endregion


//region CORE FUNCTIONS
EulTypeEnum EulFloatType::getTypeEnum() { return EulTypeEnum::FLOAT_TYPE; }
//endregion


//region CODE GENERATION
llvm::Value* EulFloatType::castIntToFloatValue(llvm::Value* sourceValue, EulIntegerType* sourceType, EulCodeGenContext* ctx) {
    //Int casting takes in account whether the source integer type is unsigned or not.
    //Different llvm instructions are involved if it is so.
    if (sourceType->isUnsigned) return ctx->builder.CreateUIToFP(sourceValue, this->getLlvmType(ctx));
    else return ctx->builder.CreateSIToFP(sourceValue, this->getLlvmType(ctx));
}

llvm::Value* EulFloatType::castFloatToFloatValue(llvm::Value* sourceValue, EulFloatType* sourceType, EulCodeGenContext* ctx) {
    if (this->size == sourceType->size) return sourceValue;
    else if(this->size < sourceType->size) return ctx->builder.CreateFPTrunc(sourceValue, this->getLlvmType(ctx));
    else return ctx->builder.CreateFPExt(sourceValue, this->getLlvmType(ctx));
}

llvm::Value* EulFloatType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    //NOTE at the moment only int->float and float->floats castings are allowed.

    //1. Check that the source type is indeed an integer
    switch (sourceType->getTypeEnum()) {
        case EulTypeEnum::INT_TYPE:
            return this->castIntToFloatValue(sourceValue, static_cast<EulIntegerType*>(sourceType), ctx);

        case EulTypeEnum::FLOAT_TYPE:
             return this->castFloatToFloatValue(sourceValue, static_cast<EulFloatType*>(sourceType), ctx);

        default: throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED only ints and floats can be casted to float.");
    }
}

llvm::Type* EulFloatType::getLlvmType(EulCodeGenContext* ctx) {
    switch(this->size) {
        case 32: return llvm::Type::getFloatTy(ctx->context);
        case 64: return llvm::Type::getDoubleTy(ctx->context);
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid floating point size: " + std::to_string(this->size)+". Please use one of 32, 64.");
    }
}
//endregion


//region SERIALIZATION
void EulFloatType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulFloatType\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"size\":" << (int)this->size << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
