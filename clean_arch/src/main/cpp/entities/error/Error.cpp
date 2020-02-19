#include "EulException.h"
#include "VariableAlreadyDeclaredException.h"

EulException::EulException(const std::string& className, const std::string& message) :
  className(className),
  message(message) {}

VariableAlreadyDeclaredException::VariableAlreadyDeclaredException(const std::string& message) :
  EulException("VariableAlreadyDeclaredException", message) {}
