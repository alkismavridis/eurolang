#include <string>

#include "BooleanNode.h"
#include "CharNode.h"
#include "FloatNode.h"
#include "IntNode.h"
#include "StringNode.h"
#include "SymbolNameNode.h"

using namespace std;

BooleanNode::BooleanNode(bool value) :
  value(value) {}

CharNode::CharNode(unsigned long int value, unsigned char size) :
  value(value),
  size(size) {}

FloatNode::FloatNode(double value, unsigned char size) :
  value(value),
  size(size) {}

IntNode::IntNode(unsigned long int value, unsigned char size, bool isUnsigned) :
  value(value),
  size(size),
  isUnsigned(isUnsigned) {}

StringNode::StringNode(const std::string& value) :  value(value) {}

SymbolNameNode::SymbolNameNode(const std::string& name) :  name(name) {}
