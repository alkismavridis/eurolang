#pragma once

#include <string>
#include "ast/AstNode.h"

struct EulException {
	const std::string className;
	const std::string message;
	const AstLocation location;

	EulException(const std::string& className, const std::string& message, AstLocation location);
};
