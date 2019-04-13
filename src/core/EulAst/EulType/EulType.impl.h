#pragma once


//region BASE CLASS
EulAstType EulType::getAstType() { return EulAstType::EUL_TYPE; }

bool EulType::isEulType(EulNode* tok) {
    if (tok->getType() != EulTokenType::AST) return false;
    if (static_cast<EulAst*>(tok)->getAstType() != EulAstType::EUL_TYPE) return false;
    return true;
}

std::shared_ptr<EulType> EulType::getPointerTo(unsigned char depth) {
    return std::make_shared<EulPointerType>(this, depth);
}

EulTypeEnum EulType::getTypeEnum() { return EulTypeEnum::VOID_TYPE; }
//endregion



//region ANY TYPE
EulAnyType::EulAnyType() {}

void EulAnyType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulAnyType\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulTypeEnum EulAnyType::getTypeEnum() { return EulTypeEnum::ANY_TYPE; }
//endregion



//region INT TYPE
EulIntegerType::EulIntegerType(unsigned char size, bool isUnsigned) {
    this->size = size;
    this->isUnsigned = isUnsigned;
}

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

EulTypeEnum EulIntegerType::getTypeEnum() { return EulTypeEnum::INT_TYPE; }
//endregion


//region CHAR TYPE
EulCharType::EulCharType(unsigned char size) {
    this->size = size;
}

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

EulTypeEnum EulCharType::getTypeEnum() { return EulTypeEnum::CHAR_TYPE; }
//endregion



//region FLOAT TYPE
EulFloatType::EulFloatType(unsigned char size) {
    this->size = size;
}

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

EulTypeEnum EulFloatType::getTypeEnum() { return EulTypeEnum::FLOAT_TYPE; }
//endregion





//region STRING TYPE
EulStringType::EulStringType() {}

void EulStringType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulStringType\"" << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulTypeEnum EulStringType::getTypeEnum() { return EulTypeEnum::STRING_TYPE; }
//endregion


//region NAMED TYPES
EulNamedType::EulNamedType(const std::string& name) {
    this->name = name;
}

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

EulTypeEnum EulNamedType::getTypeEnum() { return EulTypeEnum::NAMED_TYPE; }
//endregion



//region POINTER TYPES
EulPointerType::EulPointerType(EulType* contentType, unsigned char depth) {
    this->contentType = contentType;
    this->depth = depth;
}

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

EulTypeEnum EulPointerType::getTypeEnum() { return EulTypeEnum::POINTER_TYPE; }
//endregion



//region BOOLEAN TYPES
void EulBooleanType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulBooleanType\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulTypeEnum EulBooleanType::getTypeEnum() { return EulTypeEnum::BOOLEAN_TYPE; }
//endregion


//region VOID TYPES
void EulVoidType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulVoidType\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulTypeEnum EulVoidType::getTypeEnum() { return EulTypeEnum::VOID_TYPE; }
//endregion



//region FUNCTION TYPES
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
    EulNode::toJson(out, *tokenVector, tabs+1);
    out << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

bool EulFunctionType::isParameterCountValid(unsigned int paramCount) {
    if (this->varArgsType==nullptr) return paramCount == this->argTypes.size();
    else return paramCount >= this->argTypes.size();
}


EulTypeEnum EulFunctionType::getTypeEnum() { return EulTypeEnum::FUNCTION_TYPE; }
//endregion
