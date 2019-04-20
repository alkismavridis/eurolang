#pragma once


int StarOperator::getOperatorType() {
    return yy::EulParser::token::STAR;
}

const std::string StarOperator::getOperatorText() {
    return "*";
}

bool StarOperator::isAssignment() { return false; }

llvm::Value* StarOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    //1. Calculate result type
    auto targetEulType = EulType::doCommonNumberMerging(leftType, rightType, ctx);
    auto targetLlvmType = targetEulType->getLlvmType(ctx);

    //2. Cast operands, if needed
    if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
    if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = targetEulType;

     //3. Create an instruction based on the result type
    if (targetEulType->getTypeEnum() == EulTypeEnum::INT_TYPE) return ctx->builder.CreateMul(left, right);
    else return ctx->builder.CreateFMul(left, right);
}
