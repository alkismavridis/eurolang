#pragma once

#include "EulType.h"

struct IntType : public EulType {
	const unsigned char size;
	const bool isUnsigned;

	IntType(unsigned char size, bool isUnsigned) :
		size(size),
		isUnsigned(isUnsigned) {}
};
