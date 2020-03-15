#pragma once

#include <string>
#include "model/error/EulException.h"

struct ValueTypeNotSetException : public EulException {
	ValueTypeNotSetException(const std::string& message, AstLocation location);
};
