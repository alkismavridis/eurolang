#include "AstMetadata.h"
#include "analyzer/model/error/ValueTypeAlreadySetException.h"
#include "analyzer/model/error/ValueTypeNotSetException.h"
#include <iostream>

bool AstMetadata::hasErrors() {
  return !this->errors.empty();
}


void AstMetadata::addError(std::unique_ptr<const EulException> error) {
  this->errors.push_back(move(error));
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
