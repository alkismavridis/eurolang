#pragma once

int NotOperator::getOperatorType() {
    return yy::EulParser::token::NOT;
}

const std::string NotOperator::getOperatorText() {
    return "!";
}

bool NotOperator::isAssignment() { return false; }


llvm::Value* NotOperator::performPrefix(llvm::Value* arg, std::shared_ptr<EulType> argType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
  //1. Convert incoming value to boolean
  if(argType != ctx->compiler->program.nativeTypes.booleanType) {
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "! operator works only with booleans (at the moment...)");
  }

  //2. Convert the value to the target type, if needed
  auto targetLlvmType = argType->getLlvmType(ctx);
  if (targetLlvmType != arg->getType()) arg = argType->castValue(arg, argType.get(), false, ctx);
  *resultTypeAddr = ctx->compiler->program.nativeTypes.booleanType;

  return  ctx->builder.CreateICmpEQ(arg, llvm::ConstantInt::get(ctx->context, llvm::APInt(1, 0, true)));
}
