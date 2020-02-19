#pragma once

#include "SymbolChangeType.h"
#include "../types/EulType.h"
#include "../values/EulValue.h"

struct SymbolDeclaration {
  const SymbolChangeType changeType;
  const EulType* const varType; //At the moment, not all symbols have a type. Primitive type symbols, for example give nullptr here. We might add a nativeTypeType in the future to cover this gap.
  const EulValue* const value; //is any if provided

  SymbolDeclaration(SymbolChangeType changeType, EulType* varType, EulValue* value);
};
