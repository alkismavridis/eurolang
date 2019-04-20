#pragma once


//region LIFE CYCLE
EulCharType::EulCharType(unsigned char size) {
    this->size = size;
}
//endregion



//region CORE FUNCTIONS
EulTypeEnum EulCharType::getTypeEnum() { return EulTypeEnum::CHAR_TYPE; }
//endregion



//region CODE GENERATION
llvm::Value* EulCharType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED EulCharType::castValue.");
}

llvm::Type* EulCharType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, this->size);
}
//endregion



//region SERIALIZATION
void EulCharType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulCharType\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"size\":" << (int)this->size << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
