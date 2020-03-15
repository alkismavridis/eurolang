#include <string>

#include "EulValue.h"
#include "BooleanNode.h"
#include "CharNode.h"
#include "FloatNode.h"
#include "IntNode.h"
#include "StringNode.h"
#include "SymbolNameNode.h"

using namespace std;

EulValue::EulValue(AstLocation location) : AstNode(location) {}


BooleanNode::BooleanNode(bool value, AstLocation location) :
	EulValue(location),
	value(value) {}

CharNode::CharNode(unsigned long int value, unsigned char size, AstLocation location) :
	EulValue(location),
	value(value),
	size(size) {}

FloatNode::FloatNode(double value, unsigned char size, AstLocation location) :
	EulValue(location),
	value(value),
	size(size) {}

IntNode::IntNode(unsigned long int value, unsigned char size, bool isUnsigned, AstLocation location) :
	EulValue(location),
	value(value),
	size(size),
	isUnsigned(isUnsigned) {}

StringNode::StringNode(const std::string& value, AstLocation location) :
	EulValue(location),
	value(value) {}

SymbolNameNode::SymbolNameNode(const std::string& name, AstLocation location) :
	EulValue(location),
	name(name) {}
