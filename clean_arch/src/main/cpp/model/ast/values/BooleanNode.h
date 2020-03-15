#pragma once

#include "EulValue.h"

struct BooleanNode : public EulValue {
	const bool value;

	BooleanNode(const bool val, AstLocation location);
};
