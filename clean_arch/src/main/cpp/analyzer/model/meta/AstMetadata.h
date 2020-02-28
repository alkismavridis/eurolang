#pragma once

#include <list>
#include <unordered_map>
#include <memory>

#include "ast/values/EulValue.h"

#include "analyzer/model/types/EulType.h"
#include "analyzer/model/error/EulException.h"
#include "analyzer/model/scope/EulScope.h"

/** This holds the results of the analyzed ast */
class AstMetadata {

  /** Every value on the ast, including functions and expressions must have a type */
  std::unordered_map<const EulValue*, const EulType*> valueTypes;

  /** Elements such as functions and code blocks also have a scope associated with them*/
  std::unordered_map<void*, std::unique_ptr<EulScope>> scopes;
  std::list<std::unique_ptr<const EulException>> errors;

  /**
      Some types (such as function signatures) are generated on the fly during
      ast analysing. We save those here, plus a reference in valueTypes map, as usual.
   */
  std::list<std::unique_ptr<const EulType>> ownedTypes;


public:
  bool hasErrors();
  void addError(std::unique_ptr<const EulException> error);

  const EulType* getTypeFor(const EulValue* value);
  const EulType* requireTypeFor(const EulValue* value);
  void putType(const EulValue* value, const EulType* type);

  void putAndOwnType(const EulValue* value, std::unique_ptr<const EulType> type);

  EulScope* getScopeFor(void* astNode);
  EulScope* requireScopeFor(void* astNode);
  EulScope* getOrCreateScopeFor(void* astNode);
};
