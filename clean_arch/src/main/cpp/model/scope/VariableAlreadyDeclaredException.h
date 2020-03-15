#pragma once

#include <string>
#include "model/error/EulException.h"

struct VariableAlreadyDeclaredException : public EulException {
	const AstLocation prevDeclarationLoacation;

	VariableAlreadyDeclaredException(const std::string& message, AstLocation prevDeclarationLoacation, AstLocation location);
};
