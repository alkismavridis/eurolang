#include "ast/statements/SymbolChangeType.h"
#include "EulScope.h"
#include "VariableAlreadyDeclaredException.h"

using namespace std;

// SymbolDeclaration
SymbolDeclaration::SymbolDeclaration(SymbolChangeType changeType, const EulType* varType, const EulValue* value, AstLocation location) :
	changeType(changeType),
	varType(varType),
	value(value),
	location(location) {}




// EulScope
EulScope::EulScope(EulScope* parent) :
	parent(parent) {}


const SymbolDeclaration* EulScope::get(const string& key) const {
	auto entry = this->declarations.find(key);
	if (entry != this->declarations.end()) {
		return entry->second.get();
	}

	if (this->parent != nullptr) {
		return this->parent->get(key);
	}
	return nullptr;
}


void EulScope::declare(SymbolChangeType changeType, const string& key, const EulType* type, const EulValue* value, AstLocation location) {
	const auto entry = this->declarations.find(key);

	if (entry != this->declarations.end()) {
		throw VariableAlreadyDeclaredException("Variable " + key + " is already defined.", entry->second->location, location);
	}

	this->declarations[key] = make_unique<SymbolDeclaration>(changeType, type, value, location);
}



//SECTION Exceptions
VariableAlreadyDeclaredException::VariableAlreadyDeclaredException(const std::string& message, AstLocation prevDeclarationLoacation, AstLocation location) :
	EulException("VariableAlreadyDeclaredException", message, location),
	prevDeclarationLoacation(prevDeclarationLoacation) {}
