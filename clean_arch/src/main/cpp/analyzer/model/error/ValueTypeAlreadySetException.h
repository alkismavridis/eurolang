#pragma once

#include <string>
#include "EulException.h"

struct ValueTypeAlreadySetException : public EulException {
  ValueTypeAlreadySetException(const std::string& message, AstLocation location);
};
