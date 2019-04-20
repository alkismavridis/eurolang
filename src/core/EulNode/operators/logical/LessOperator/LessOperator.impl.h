#pragma once

int LessOperator::getOperatorType() {
    return yy::EulParser::token::LESS;
}

const std::string LessOperator::getOperatorText() {
    return "<";
}

bool LessOperator::isAssignment() { return false; }

llvm::Value* LessOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    //1. Calculate result type
    auto targetEulType = EulType::doCommonNumberMerging(leftType, rightType, ctx);
    auto targetLlvmType = targetEulType->getLlvmType(ctx);

    //2. Cast operands, if needed
    if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
    if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = ctx->compiler->program.nativeTypes.booleanType;

     //3. Create an instruction based on the result type
    if (targetEulType->getTypeEnum() == EulTypeEnum::INT_TYPE) {
        auto asInt = static_cast<EulIntegerType*>(targetEulType.get());
        return asInt->isUnsigned?
            ctx->builder.CreateICmpULT(left, right) :
            ctx->builder.CreateICmpSLT(left, right);
    }
    else return ctx->builder.CreateFCmpULT(left, right); //TODO ordered or unordered?
}
