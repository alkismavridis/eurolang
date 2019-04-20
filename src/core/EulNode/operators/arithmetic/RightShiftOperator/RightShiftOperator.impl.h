#pragma once


int RightShiftOperator::getOperatorType() {
    return yy::EulParser::token::RSHIFT;
}

const std::string RightShiftOperator::getOperatorText() {
    return ">>";
}

bool RightShiftOperator::isAssignment() { return false; }

llvm::Value* RightShiftOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    auto targetEulType = EulType::doCommonIntMerging(leftType, rightType, ctx);
    auto targetLlvmType = static_cast<llvm::IntegerType*>(targetEulType->getLlvmType(ctx));

    if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
    if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = targetEulType;

    return targetEulType->isUnsigned?
        ctx->builder.CreateLShr(left, right) :
        ctx->builder.CreateAShr(left, right);
}
