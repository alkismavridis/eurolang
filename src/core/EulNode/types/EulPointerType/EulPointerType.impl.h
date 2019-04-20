#pragma once


//region LIFE CYCLE
EulPointerType::EulPointerType(EulType* contentType, unsigned char depth) {
    this->contentType = contentType;
    this->depth = depth;
}
//endregion



//region CORE FUNCTIONS
EulTypeEnum EulPointerType::getTypeEnum() { return EulTypeEnum::POINTER_TYPE; }
//endregion



//region CODE GENERATION
llvm::Value* EulPointerType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED EulPointerType::castValue.");
}

llvm::Type* EulPointerType::getLlvmType(EulCodeGenContext* ctx) {
    auto type = this->contentType->getLlvmType(ctx);
    for (int i = this->depth; i--;) type = type->getPointerTo();
    return type;
}
//endregion



//region SERIALIZATION
void EulPointerType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulPointerType\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"depth\": " << (int)this->depth << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"contentType\": ";
    contentType->toJson(out, tabs+1);
    out << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
