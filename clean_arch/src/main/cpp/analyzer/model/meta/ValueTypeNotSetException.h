#pragma once

#include <string>
#include "analyzer/model/error/EulException.h"

struct ValueTypeNotSetException : public EulException {
  ValueTypeNotSetException(const std::string& message, AstLocation location);
};
