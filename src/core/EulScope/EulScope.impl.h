#pragma once

////region LIFE CYCLE
EulScope::EulScope(EulScope* superScope) {
    this->superScope = superScope;
}


EulScope::~EulScope() {
    for (auto const& decl : this->declarations) delete decl.second;
}

void EulScope::reset() {
    for (auto const& decl : this->declarations) delete decl.second;
    this->declarations.clear();
}
//endregion



//region DECLARATION MANAGEMENT
EulSymbol* EulScope::get(const std::string& key) {
    //1. Try to find it on this scope.
    auto entry = this->declarations.find(key);

    //2. If found, return it.
    if (entry != this->declarations.end()) return entry->second;

    //3. We did not find the symbol. Search in parent scope, if any
    if (this->superScope != nullptr) return this->superScope->get(key);

    //4. If we are the root scope, and symbol was not found, return null.
    return nullptr;
}

EulSymbol* EulScope::getOwnSymbol(const std::string& key) {
    //1. Try to find it on this scope.
    auto entry = this->declarations.find(key);

    //2. If found, return it.
    if (entry != this->declarations.end()) return entry->second;

    //3. otherwise, return null.
    return nullptr;
}


int EulScope::getDeclarationCount() {
    return this->declarations.size();
}

bool EulScope::declare(const std::string& key, EulSymbol* symbol) {
    //1. Try to find it on this scope.
    auto entry = this->declarations.find(key);

    //2. If found, throw an exception.
    if (entry != this->declarations.end()) return false;

    //3. Declare the symbol
    this->declarations[key] = symbol;
    return true;
}
//endregion