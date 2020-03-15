#include "model/ast/statements/SymbolChangeType.h"
#include "EulScope.h"
#include "VariableAlreadyDeclaredException.h"

using namespace std;

/// SymbolDeclaration
SymbolDeclaration::SymbolDeclaration(SymbolChangeType changeType, const EulType* varType, const EulValue* value, AstLocation location) :
	changeType(changeType),
	varType(varType),
	value(value),
	location(location) {}


/// EulScope
EulScope::EulScope(EulScope* parent) :
	parent(parent) {}


const SymbolDeclaration* EulScope::getSymbol(const string& key) const {
	auto entry = this->symbolDeclarations.find(key);
	if (entry != this->symbolDeclarations.end()) {
		return entry->second.get();
	}

	if (this->parent != nullptr) {
		return this->parent->getSymbol(key);
	}

	return nullptr;
}

void EulScope::declareSymbol(SymbolChangeType changeType, const string& key, const EulType* type, const EulValue* value, AstLocation location) {
	const auto entry = this->symbolDeclarations.find(key);

	if (entry != this->symbolDeclarations.end()) {
		throw VariableAlreadyDeclaredException("Variable " + key + " is already defined.", entry->second->location, location);
	}

	this->symbolDeclarations[key] = make_unique<SymbolDeclaration>(changeType, type, value, location);
}

const EulType* EulScope::getType(const std::string& key) const {
	auto entry = this->typeDeclarations.find(key);
	if (entry != this->typeDeclarations.end()) {
		return entry->second.get()->varType;
	}

	if (this->parent != nullptr) {
		return this->parent->getType(key);
	}

	return nullptr;
}

void EulScope::declareType(const std::string& key, const EulType* type, AstLocation location) {
	const auto entry = this->typeDeclarations.find(key);

	if (entry != this->typeDeclarations.end()) {
		throw VariableAlreadyDeclaredException("Type " + key + " is already defined.", entry->second->location, location);
	}

	this->typeDeclarations[key] = make_unique<SymbolDeclaration>(SymbolChangeType::CONST, type, nullptr, location);
}


/// Exceptions
VariableAlreadyDeclaredException::VariableAlreadyDeclaredException(const std::string& message, AstLocation prevDeclarationLoacation, AstLocation location) :
	EulException("VariableAlreadyDeclaredException", message, location),
	prevDeclarationLoacation(prevDeclarationLoacation) {}
