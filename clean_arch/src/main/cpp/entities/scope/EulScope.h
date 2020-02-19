#pragma once

#include <map>

#include "SymbolDeclaration.h"

struct EulScope {
  const EulScope* const parent;
  private: std::map<std::string, SymbolDeclaration*> declarations;


  public: EulScope(EulScope* parent);


  SymbolDeclaration* get(const std::string& key) const;
  SymbolDeclaration* getOwnSymbol(const std::string& key) const;
  EulType* getOwnSymbolAsType(const std::string& key) const;
  int getDeclarationCount() const;

  /**
      Declares the symbol, if it is not already declared on this scope (parent scopes are not included on the search).
      Returns true if the declaration was successful. false if the symbol was already defined in this scope.
  */
  void declare(const std::string& key, SymbolDeclaration* symbol);
};
