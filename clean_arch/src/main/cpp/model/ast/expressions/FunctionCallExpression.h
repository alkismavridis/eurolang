#pragma once

#include <vector>
#include <memory>

#include "model/ast/values/EulValue.h"

struct FunctionCallExpression : public EulValue {
	const std::unique_ptr<const EulValue> func;
	const std::vector<std::unique_ptr<const EulValue>> params;

	FunctionCallExpression(std::unique_ptr<const EulValue> func, std::vector<std::unique_ptr<const EulValue>> params, AstLocation location);
};
