#include <vector>

#include "InfixExpression.h"
#include "PrefixExpression.h"
#include "SuffixExpression.h"
#include "ArrayAccessExpression.h"
#include "FunctionCallExpression.h"

using namespace std;

InfixExpression::InfixExpression(EulValue* left, EulOperator* oper, EulValue* right) {
  this->left = left;
  this->oper = oper;
  this->right = right;
}

PrefixExpression::PrefixExpression(EulOperator* oper, EulValue* right) {
  this->oper = oper;
  this->right = right;
}

SuffixExpression::SuffixExpression(EulValue* left, EulOperator* oper) {
  this->left = left;
  this->oper = oper;
}

FunctionCallExpression::FunctionCallExpression(EulValue* func) {
  this->func = func;
}

FunctionCallExpression* FunctionCallExpression::addParam(EulValue* param) {
  this->params.push_back(param);
  return this;
}

ArrayAccessExpression::ArrayAccessExpression(EulValue* arr, EulValue* index) {
  this->arr = arr;
  this->index = index;
}
