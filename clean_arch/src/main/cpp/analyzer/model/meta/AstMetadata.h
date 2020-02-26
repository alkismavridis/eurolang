#pragma once

#include <list>
#include <unordered_map>
#include <memory>

#include "ast/values/EulValue.h"

#include "analyzer/types/EulType.h"
#include "analyzer/model/error/EulException.h"
#include "analyzer/model/scope/EulScope.h"

class AstMetadata {
  std::unordered_map<const EulValue*, const EulType*> valueTypes;
  std::unordered_map<void*, std::unique_ptr<EulScope>> scopes;
  std::list<std::unique_ptr<const EulException>> errors;


public:
  bool hasErrors();
  void addError(std::unique_ptr<const EulException> error);

  const EulType* getTypeFor(const EulValue* value);
  const EulType* requireTypeFor(const EulValue* value);
  void putType(const EulValue* value, const EulType* type);

  EulScope* getScopeFor(void* astNode);
  EulScope* requireScopeFor(void* astNode);
  EulScope* getOrCreateScopeFor(void* astNode);
};
