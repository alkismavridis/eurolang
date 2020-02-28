#pragma once

#include "EulType.h"

struct FunctionType : public EulType {
  const EulType* const retType;
  const std::vector<const EulType*> argTypes; //This vector does NOT include var args.
  const EulType* const varArgsType;           //null means no varargs

  FunctionType(EulType* retType, std::vector<const EulType*>& argTypes, EulType* varArgsType) :
    retType(retType),
    argTypes(std::move(argTypes)),
    varArgsType(varArgsType) {}
};
