#pragma once

////region LIFE CYCLE
EulScope::EulScope(std::shared_ptr<EulScope> superScope) {
    this->superScope = superScope;
}

void EulScope::reset() {
    this->declarations.clear();
}
//endregion



//region DECLARATION MANAGEMENT
std::shared_ptr<EulSymbol> EulScope::get(const std::string& key) {
    //1. Try to find it on this scope.
    auto entry = this->declarations.find(key);

    //2. If found, return it.
    if (entry != this->declarations.end()) return entry->second;

    //3. We did not find the symbol. Search in parent scope, if any
    if (this->superScope != nullptr) return this->superScope->get(key);

    //4. If we are the root scope, and symbol was not found, return null.
    return nullptr;
}

std::shared_ptr<EulSymbol> EulScope::getOwnSymbol(const std::string& key) {
    //1. Try to find it on this scope.
    auto entry = this->declarations.find(key);

    //2. If found, return it.
    if (entry != this->declarations.end()) return entry->second;

    //3. otherwise, return null.
    return nullptr;
}


EulType* EulScope::getOwnSymbolAsType(const std::string& key) {
    //1. Try to find it on this scope.
    auto symbol = this->getOwnSymbol(key);

    //2. Check the existence of the symbol, and that it contains a type
    if (symbol==nullptr || !EulType::isEulType(symbol->value.get()))
        throw EulError(EulErrorType::SEMANTIC, "Type not found: " + key);

    //3. Cast it and return it
    return static_cast<EulType*>(symbol->value.get());
}


int EulScope::getDeclarationCount() {
    return this->declarations.size();
}

bool EulScope::declare(const std::string& key, std::shared_ptr<EulSymbol> symbol) {
    //1. Try to find it on this scope.
    auto entry = this->declarations.find(key);

    //2. If found, throw an exception.
    if (entry != this->declarations.end()) throw EulError(EulErrorType::SEMANTIC, "Symbol "+key+" already defined on this scope.");

    //3. Declare the symbol
    this->declarations[key] = symbol;
    return true;
}


void EulScope::declare(VarDeclarationStatement* stmt) {
    for (auto decl: *stmt->declarations) {
        this->declare(decl->id->name, std::make_shared<EulSymbol>(stmt->varType, decl->varType, decl));
    }
}
//endregion






//region EUL SYMBOL
EulSymbol::EulSymbol(int changeType, std::shared_ptr<EulType> varType, std::shared_ptr<EulToken> value) {
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
//endregion
