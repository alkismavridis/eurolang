#include "EulScope.h"
#include "SymbolChangeType.h"
#include "../error/VariableAlreadyDeclaredException.h"

// SymbolDeclaration
SymbolDeclaration::SymbolDeclaration(SymbolChangeType changeType, EulType* varType, EulValue* value) :
  changeType(changeType),
  varType(varType),
  value(value) {}




// EulScope
EulScope::EulScope(EulScope* parent) :
  parent(parent) {}


SymbolDeclaration* EulScope::get(const std::string& key) const {
  auto entry = this->declarations.find(key);
  if (entry != this->declarations.end()) {
    return entry->second;
  }

  if (this->parent != nullptr) {
    return this->parent->get(key);
  }
  return nullptr;
}


void EulScope::declare(const std::string& key, SymbolDeclaration* symbol) {
  const auto entry = this->declarations.find(key);

  //2. If found, throw an exception.
  if (entry != this->declarations.end()) {
    throw VariableAlreadyDeclaredException("Variable " + key + " is already defined.");
  }

  //3. Declare the symbol
  this->declarations[key] = symbol;
}
