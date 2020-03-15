#pragma once

#include <string>
#include "model/ast/AstNode.h"

struct EulException {
	const std::string className;
	const std::string message;
	const AstLocation location;

	EulException(const std::string& className, const std::string& message, AstLocation location);
};
