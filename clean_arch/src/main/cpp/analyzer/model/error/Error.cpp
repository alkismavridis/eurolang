#include "EulException.h"
#include "VariableAlreadyDeclaredException.h"
#include "ValueTypeAlreadySetException.h"
#include "ValueTypeNotSetException.h"

EulException::EulException(const std::string& className, const std::string& message, AstLocation location) :
  location(location),
  className(className),
  message(message) {}

VariableAlreadyDeclaredException::VariableAlreadyDeclaredException(const std::string& message, AstLocation prevDeclarationLoacation, AstLocation location) :
  EulException("VariableAlreadyDeclaredException", message, location),
  prevDeclarationLoacation(prevDeclarationLoacation) {}

ValueTypeAlreadySetException::ValueTypeAlreadySetException(const std::string& message, AstLocation location) :
  EulException("ValueTypeAlreadySetException", message, location) {}

ValueTypeNotSetException::ValueTypeNotSetException(const std::string& message, AstLocation location) :
  EulException("ValueTypeNotSetException", message, location) {}
