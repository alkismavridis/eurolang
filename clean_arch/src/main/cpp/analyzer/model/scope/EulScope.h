#pragma once

#include <memory>
#include <unordered_map>

#include "SymbolDeclaration.h"

struct EulScope {
  const EulScope* const parent;
  private: std::unordered_map<std::string, std::unique_ptr<const SymbolDeclaration>> declarations;


  public: EulScope(EulScope* parent);


  const SymbolDeclaration* get(const std::string& key) const;
  const SymbolDeclaration* getOwnSymbol(const std::string& key) const;
  const EulType* getOwnSymbolAsType(const std::string& key) const;
  int getDeclarationCount() const;

  /**
      Declares the symbol, if it is not already declared on this scope (parent scopes are not included on the search).
      Returns true if the declaration was successful. false if the symbol was already defined in this scope.
  */
  void declare(SymbolChangeType changeType, const std::string& key, const EulType* type, const EulValue* value, AstLocation location);
};
