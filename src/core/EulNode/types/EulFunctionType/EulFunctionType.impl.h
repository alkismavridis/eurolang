#pragma once


//region LIFE CYCLE
EulFunctionType::EulFunctionType(const std::shared_ptr<EulType> retType) {
    this->retType = retType;
    this->varArgsType = nullptr;
}

EulFunctionType::EulFunctionType(const std::shared_ptr<EulType> retType, std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> argDeclarations) {
    this->retType = retType;
    this->varArgsType = nullptr;
    if (argDeclarations != nullptr) {
        for (auto param : *argDeclarations) {
            this->argTypes.push_back(param->varType);
        }
    }
}

EulFunctionType::EulFunctionType(
  const std::shared_ptr<EulType> retType,
  std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> argDeclarations,
  const std::shared_ptr<EulType> varArgsType)
{
    this->retType = retType;
    this->varArgsType = varArgsType;
    if (argDeclarations != nullptr) {
        for (auto param : *argDeclarations) {
            this->argTypes.push_back(param->varType);
        }
    }
}
//endregion



//region CORE FUNCTIONS
EulTypeEnum EulFunctionType::getTypeEnum() { return EulTypeEnum::FUNCTION_TYPE; }

bool EulFunctionType::isParameterCountValid(unsigned int paramCount) {
    if (this->varArgsType==nullptr) return paramCount == this->argTypes.size();
    else return paramCount >= this->argTypes.size();
}
//endregion



//region CODE GENERATION
llvm::Value* EulFunctionType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED EulFunctionType::castValue.");
}

llvm::Type* EulFunctionType::getLlvmType(EulCodeGenContext* ctx) {
    //1. Build argument list
    std::vector<llvm::Type*> llvmArgList;
    for (auto const& argType : this->argTypes) llvmArgList.push_back(argType->getLlvmType(ctx));

    auto ret = llvm::FunctionType::get(
        this->retType->getLlvmType(ctx),
        llvm::ArrayRef<llvm::Type*>(llvmArgList),
        this->varArgsType != nullptr
    );

    return ret;
}
//endregion



//region SERIALIZATION
void EulFunctionType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulFunctionType\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"retType\": ";
    this->retType->toJson(out, tabs+1);
    out << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"argTypes\": ";
    auto tokenVector = (std::vector<std::shared_ptr<EulNode>>*) &this->argTypes;
    EulNode::toJsonArray(out, *tokenVector, tabs+1);
    out << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
