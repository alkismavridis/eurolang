#pragma once

#include <string>
#include "analyser/model/error/EulException.h"

struct ValueTypeAlreadySetException : public EulException {
	ValueTypeAlreadySetException(const std::string& message, AstLocation location);
};
