#pragma once

#include "EulValue.h"

struct CharNode : public EulValue {
	const unsigned long int value;
	const unsigned char size; //in bytes


	CharNode(unsigned long int value, unsigned char size, AstLocation location);
};
