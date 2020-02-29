#include <iostream>

#include "AstMetadata.h"
#include "ValueTypeAlreadySetException.h"
#include "ValueTypeNotSetException.h"

bool AstMetadata::hasErrors() {
	return !this->errors.empty();
}


void AstMetadata::addError(const EulException& error) {
	this->errors.push_back(error);
}

const EulType* AstMetadata::getTypeFor(const EulValue* value) {
	return this->valueTypes[value];
}

const EulType* AstMetadata::requireTypeFor(const EulValue* value) {
	auto existing = this->valueTypes[value];
	if (existing == nullptr) {
		throw ValueTypeNotSetException("RequiredType not present.", value->location);
	}

	return existing;
}

void AstMetadata::putType(const EulValue* value, const EulType* type) {
	auto existing = this->valueTypes[value];
	if (existing != nullptr) {
		throw ValueTypeAlreadySetException("PutType failed. Type already set.", value->location);
	}

	this->valueTypes[value] = type;
}

void AstMetadata::putAndOwnType(const EulValue* value, std::unique_ptr<const EulType> type) {
	this->putType(value, type.get());
	this->ownedTypes.push_back(move(type));
}


//SECTION Exceptions
ValueTypeAlreadySetException::ValueTypeAlreadySetException(const std::string& message, AstLocation location) :
	EulException("ValueTypeAlreadySetException", message, location) {}

ValueTypeNotSetException::ValueTypeNotSetException(const std::string& message, AstLocation location) :
	EulException("ValueTypeNotSetException", message, location) {}
