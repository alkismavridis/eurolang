#pragma once

#include <list>
#include <unordered_map>
#include <memory>

#include "ast/values/EulValue.h"
#include "ast/statements/ScopeRoot.h"

#include "analyser/model/types/EulType.h"
#include "analyser/model/error/EulException.h"
#include "analyser/model/scope/EulScope.h"

/** This holds the results of the analyzed ast */
class AstMetadata {

	/** Every value on the ast, including functions and expressions must have a type */
	std::unordered_map<const EulValue*, const EulType*> valueTypes;

	/** Elements such as functions and code blocks also have a scope associated with them*/
	std::unordered_map<ScopeRoot*, std::unique_ptr<EulScope>> scopes;
	std::list<const EulException> errors;

	/**
		Some types (such as function signatures) are generated on the fly during
		ast analysing. We save those here, plus a reference in valueTypes map, as usual.
	 */
	std::list<std::unique_ptr<const EulType>> ownedTypes;
	EulScope* const globalScope;



public:
	AstMetadata(EulScope* globalScope) : globalScope(globalScope) {}

	bool hasErrors();
	void addError(const EulException& error);

	const EulType* getTypeFor(const EulValue* value);
	const EulType* requireTypeFor(const EulValue* value);
	void putType(const EulValue* value, const EulType* type);

	void putAndOwnType(const EulValue* value, std::unique_ptr<const EulType> type);

	EulScope* getScopeFor(void* astNode);
	EulScope* requireScopeFor(void* astNode);
	EulScope* getOrCreateScopeFor(void* astNode);
};
