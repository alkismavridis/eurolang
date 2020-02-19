#pragma once

int LeftShiftOperator::getOperatorType() {
    return yy::EulParser::token::LSHIFT;
}

const std::string LeftShiftOperator::getOperatorText() {
    return "<<";
}

bool LeftShiftOperator::isAssignment() { return false; }

llvm::Value* LeftShiftOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    auto targetEulType = EulType::doCommonIntMerging(leftType, rightType, ctx);
    auto targetLlvmType = static_cast<llvm::IntegerType*>(targetEulType->getLlvmType(ctx));

    if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
    if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = targetEulType;

    return ctx->builder.CreateShl(left, right);
}