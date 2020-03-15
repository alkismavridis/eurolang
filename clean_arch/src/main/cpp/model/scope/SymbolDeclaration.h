#pragma once

#include "model/ast/statements/SymbolChangeType.h"
#include "model/ast/values/EulValue.h"

#include "model/types/EulType.h"


struct SymbolDeclaration {
	const SymbolChangeType changeType;
	const EulType* const varType; //At the moment, not all symbols have a type. Primitive type symbols, for example give nullptr here. We might add a nativeTypeType in the future to cover this gap.
	const EulValue* const value; //is any if provided
	const AstLocation location;

	SymbolDeclaration(SymbolChangeType changeType, const EulType* varType, const EulValue* value, AstLocation location);
};
