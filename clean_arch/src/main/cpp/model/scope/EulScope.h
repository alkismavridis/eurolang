#pragma once

#include <memory>
#include <unordered_map>

#include "SymbolDeclaration.h"

struct EulScope {
	const EulScope* const parent;
	private: std::unordered_map<std::string, std::unique_ptr<const SymbolDeclaration>> symbolDeclarations;
	private: std::unordered_map<std::string, std::unique_ptr<const SymbolDeclaration>> typeDeclarations;


	public: EulScope(EulScope* parent);


	const SymbolDeclaration* getSymbol(const std::string& key) const;
	const SymbolDeclaration* getOwnSymbol(const std::string& key) const;
	int getDeclarationCount() const;

	const EulType* getType(const std::string& key) const;
	const EulType* getOwnType(const std::string& key) const;
	int getTypeDeclarationCount() const;

	/**
		Declares the symbol, if it is not already declared on this scope (parent scopes are not included on the search).
		Returns true if the declaration was successful. false if the symbol was already defined in this scope.
	*/
	void declareSymbol(
		SymbolChangeType changeType,
		const std::string& key,
		const EulType* type,
		const EulValue* value,
		AstLocation location
	);

	void declareType(
		const std::string& key,
		const EulType* type,
		AstLocation location
	);
};
