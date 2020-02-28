#include "EulException.h"

EulException::EulException(const std::string& className, const std::string& message, AstLocation location) :
  location(location),
  className(className),
  message(message) {}
