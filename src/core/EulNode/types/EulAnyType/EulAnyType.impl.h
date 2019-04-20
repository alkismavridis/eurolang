#pragma once


//region LIFE CYCLE
EulAnyType::EulAnyType() {}
//endregion


//region CORE FUNCTIONS
EulTypeEnum EulAnyType::getTypeEnum() { return EulTypeEnum::ANY_TYPE; }
//endregion



//region CODE GENERATION
llvm::Value* EulAnyType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    return sourceValue;
}

llvm::Type* EulAnyType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, 8)->getPointerTo();
}
//endregion



//region SERIALIZATION
void EulAnyType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulAnyType\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
