#pragma once


//region BASE CLASS
EulAstType EulType::getAstType() { return EUL_TYPE; }

bool EulType::isEulType(EulToken* tok) {
    if (tok->getType() != AST) return false;
    if ( ((EulAst*)tok)->getAstType() != EUL_TYPE) return false;
    return true;
}

std::shared_ptr<EulType> EulType::getPointerTo(unsigned char depth) {
    return std::make_shared<EulPointerType>(this, depth);
}

EulTypeEnum EulType::getTypeEnum() { return VOID_TYPE; }
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

EulTypeEnum EulIntegerType::getTypeEnum() { return INT_TYPE; }
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

EulTypeEnum EulCharType::getTypeEnum() { return CHAR_TYPE; }
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

EulTypeEnum EulFloatType::getTypeEnum() { return FLOAT_TYPE; }
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

EulTypeEnum EulStringType::getTypeEnum() { return STRING_TYPE; }
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

EulTypeEnum EulNamedType::getTypeEnum() { return NAMED_TYPE; }
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

EulTypeEnum EulPointerType::getTypeEnum() { return POINTER_TYPE; }
//endregion


//region FUNCTION TYPES
EulFunctionType::EulFunctionType(const std::shared_ptr<EulType> retType) {
    this->retType = retType;
}

void EulFunctionType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulFunctionType\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"retType\": ";
    if (this->retType == nullptr) out << "\"void\"";
    else this->retType->toJson(out, tabs+1);
    out << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"argTypes\": ";
    auto tokenVector = (std::vector<std::shared_ptr<EulToken>>*) &this->argTypes;
    EulToken::toJson(out, *tokenVector, tabs+1);
    out << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}


EulTypeEnum EulFunctionType::getTypeEnum() { return FUNCTION_TYPE; }
//endregion