#include "OperatorNode.h"
#include "InfixExpression.h"
#include "PrefixExpression.h"
#include "SuffixExpression.h"
#include "ArrayAccessExpression.h"
#include "FunctionCallExpression.h"

using namespace std;

InfixExpression::InfixExpression(unique_ptr<const EulValue> left, unique_ptr<const OperatorNode> oper, unique_ptr<const EulValue> right, AstLocation location) :
  EulValue(location),
  left(move(left)),
  oper(move(oper)),
  right(move(right)) {}

PrefixExpression::PrefixExpression(unique_ptr<const OperatorNode> oper, unique_ptr<const EulValue> right, AstLocation location) :
  EulValue(location),
  oper(move(oper)),
  right(move(right)) {}


SuffixExpression::SuffixExpression(unique_ptr<const EulValue> left, unique_ptr<const OperatorNode> oper, AstLocation location) :
  EulValue(location),
  left(move(left)),
  oper(move(oper)) {}


FunctionCallExpression::FunctionCallExpression(unique_ptr<const EulValue> func, AstLocation location) :
  EulValue(location),
  func(move(func)) {}

FunctionCallExpression* FunctionCallExpression::addParam(unique_ptr<const EulValue> param) {
  this->params.push_back(move(param));
  return this;
}

ArrayAccessExpression::ArrayAccessExpression(unique_ptr<const EulValue> arr, unique_ptr<const EulValue> index, AstLocation location) :
  EulValue(location),
  arr(move(arr)),
  index(move(index)) {}

OperatorNode::OperatorNode(const EulOperator* eulOperator, AstLocation location) :
  AstNode(location),
  eulOperator(eulOperator) {}
