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



  // //1. Calculate result type
  // auto targetEulType = EulType::doCommonNumberMerging(leftType, rightType, ctx);
  // auto targetLlvmType = targetEulType->getLlvmType(ctx);
  //
  // //2. Cast operands, if needed
  // if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
  // if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
  // *resultTypeAddr = ctx->compiler->program.nativeTypes.booleanType;
  //
  //  //3. Create an instruction based on the result type
  // if (targetEulType->getTypeEnum() == EulTypeEnum::INT_TYPE) {
  //     auto asInt = static_cast<EulIntegerType*>(targetEulType.get());
  //     return asInt->isUnsigned?
  //         ctx->builder.CreateICmpUGE(left, right) :
  //         ctx->builder.CreateICmpSGE(left, right);
  // }
  // else return ctx->builder.CreateFCmpUGE(left, right); //TODO ordered or unordered?

}
