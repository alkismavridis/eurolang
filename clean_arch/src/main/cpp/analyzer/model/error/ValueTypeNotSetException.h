#pragma once

#include <string>
#include "EulException.h"

struct ValueTypeNotSetException : public EulException {
  ValueTypeNotSetException(const std::string& message, AstLocation location);
};
