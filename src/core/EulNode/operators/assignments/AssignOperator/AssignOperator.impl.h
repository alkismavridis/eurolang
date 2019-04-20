#pragma once

int AssignOperator::getOperatorType() { return yy::EulParser::token::ASSIGN; }
const std::string AssignOperator::getOperatorText() { return "="; }
bool AssignOperator::isAssignment() { return true; }




llvm::Value* AssignOperator::assignInfix(EulSymbol* symbol, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    //1. Cast the right expression to the symbols type.
    auto castedValue = symbol->varType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = symbol->varType;

    //2. Create the store instruction
    ctx->builder.CreateStore(castedValue, symbol->llvmValue);
    return right;
}
