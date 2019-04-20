#pragma once


EulSymbol::EulSymbol(int changeType, std::shared_ptr<EulType> varType, std::shared_ptr<EulNode> value) {
    this->changeType = changeType;
    this->varType = varType;
    this->value = value;
    this->llvmValue = nullptr;
}

EulSymbol::EulSymbol(int changeType, std::shared_ptr<EulType> varType, llvm::Value* llvmValue) {
    this->changeType = changeType;
    this->varType = varType;
    this->value = nullptr;
    this->llvmValue = llvmValue;
}

EulSymbol::EulSymbol(int changeType, std::shared_ptr<EulType> varType) {
    this->changeType = changeType;
    this->varType = varType;
    this->value = nullptr;
    this->llvmValue = nullptr;
}

void EulSymbol::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulSymbol\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"changeType\": " << this->changeType << "," << std::endl;

    //print var type
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"varType\": ";
    if (this->varType != nullptr) {
        for (int i=tabs; i>=0; --i) out << "\t";
        this->varType->toJson(out, tabs+1);
        out << "," << std::endl;
    }
    else out << "null," << std::endl;

    //print value
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"value\": ";
    if (this->value != nullptr) {
        for (int i=tabs; i>=0; --i) out << "\t";
        this->value->toJson(out, tabs+1);
        out << std::endl;
    }
    else out << "null" << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
