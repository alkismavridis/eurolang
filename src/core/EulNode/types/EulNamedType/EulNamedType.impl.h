#pragma once


//region LIFE CYCLE
EulNamedType::EulNamedType(const std::string& name) {
    this->name = name;
}
//endregion



//region CORE FUNCTIONS
EulTypeEnum EulNamedType::getTypeEnum() { return EulTypeEnum::NAMED_TYPE; }
//endregion



//region CODE GENERATION
llvm::Value* EulNamedType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED EulNamedType::castValue.");
}

llvm::Type* EulNamedType::getLlvmType(EulCodeGenContext* ctx) {
    return ctx->module->getTypeByName(this->name);
}
//endregion



//region SERIALIZATION
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
//endregion
