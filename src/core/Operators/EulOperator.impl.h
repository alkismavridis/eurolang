#pragma once



//region BASE CLASS
llvm::Value* EulOperator::performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::performPrefix was called, but should not.");
}

llvm::Value* EulOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::performInfix was called, but should not.");
}

llvm::Value* EulOperator::assignInfix(EulSymbol* symbol, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::assignInfix was called, but should not.");
}

llvm::Value* EulOperator::performSuffix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::performSuffix was called, but should not.");
}

int EulOperator::getOperatorType() {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::getOperatorType was called, but should not.");
}

const std::string EulOperator::getOperatorText() {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::getOperatorText was called, but should not.");
}

bool EulOperator::isAssignment() {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::isAssignment was called, but should not.");
}
//endregion




#include "AssignOperator/AssignOperator.impl.h"




//region AssignModOperator
int AssignModOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_MOD;
}

const std::string AssignModOperator::getOperatorText() {
    return "=%";
}

bool AssignModOperator::isAssignment() { return true; }
//endregion



//region AssignXorOperator
int AssignXorOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_XOR;
}

const std::string AssignXorOperator::getOperatorText() {
    return "=^";
}

bool AssignXorOperator::isAssignment() { return true; }
//endregion



//region AssignAndOperator
int AssignAndOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_AND;
}

const std::string AssignAndOperator::getOperatorText() {
    return "=&";
}

bool AssignAndOperator::isAssignment() { return true; }
//endregion




//region AssignStarOperator
int AssignStarOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_STAR;
}

const std::string AssignStarOperator::getOperatorText() {
    return "=*";
}

bool AssignStarOperator::isAssignment() { return true; }
//endregion


//region AssignMinusOperator
int AssignMinusOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_MINUS;
}

const std::string AssignMinusOperator::getOperatorText() {
    return "=-";
}

bool AssignMinusOperator::isAssignment() { return true; }
//endregion


//region AssignPlusOperator
int AssignPlusOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_PLUS;
}

const std::string AssignPlusOperator::getOperatorText() {
    return "=+";
}

bool AssignPlusOperator::isAssignment() { return true; }
//endregion


//region AssignOrOperator
int AssignOrOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_OR;
}

const std::string AssignOrOperator::getOperatorText() {
    return "=|";
}

bool AssignOrOperator::isAssignment() { return true; }
//endregion


//region AssignDivOperator
int AssignDivOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_DIV;
}

const std::string AssignDivOperator::getOperatorText() {
    return "=/";
}

bool AssignDivOperator::isAssignment() { return true; }
//endregion


//region AssignLeftShiftOperator
int AssignLeftShiftOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_LSHIFT;
}

const std::string AssignLeftShiftOperator::getOperatorText() {
    return "=<<";
}

bool AssignLeftShiftOperator::isAssignment() { return true; }
//endregion


//region AssignLeftShiftOperator
int AssignRightShiftOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_RSHIFT;
}

const std::string AssignRightShiftOperator::getOperatorText() {
    return "=>>";
}

bool AssignRightShiftOperator::isAssignment() { return true; }
//endregion




//region OrOperator
int OrOperator::getOperatorType() {
    return yy::EulParser::token::OR;
}

const std::string OrOperator::getOperatorText() {
    return "||";
}

bool OrOperator::isAssignment() { return false; }
//endregion

//region AndOperator
int AndOperator::getOperatorType() {
    return yy::EulParser::token::AND;
}

const std::string AndOperator::getOperatorText() {
    return "&&";
}

bool AndOperator::isAssignment() { return false; }
//endregion


//region XorOperator
int XorOperator::getOperatorType() {
    return yy::EulParser::token::XOR;
}

const std::string XorOperator::getOperatorText() {
    return "^";
}

bool XorOperator::isAssignment() { return false; }
//endregion


//region NotEqualsOperator
int NotEqualsOperator::getOperatorType() {
    return yy::EulParser::token::NOT_EQUALS;
}

const std::string NotEqualsOperator::getOperatorText() {
    return "!=";
}

bool NotEqualsOperator::isAssignment() { return false; }

llvm::Value* NotEqualsOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    //1. Calculate result type
    auto targetEulType = EulType::doCommonNumberMerging(leftType, rightType, ctx);
    auto targetLlvmType = targetEulType->getLlvmType(ctx);

    //2. Cast operands, if needed
    if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
    if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = ctx->compiler->program.nativeTypes.booleanType;

     //3. Create an instruction based on the result type
    if (targetEulType->getTypeEnum() == EulTypeEnum::INT_TYPE) return ctx->builder.CreateICmpNE(left, right);
    else return ctx->builder.CreateFCmpUNE(left, right); //TODO UNE or ONE?
}
//endregion

//region NotSameOperator
int NotSameOperator::getOperatorType() {
    return yy::EulParser::token::NOT_SAME;
}

const std::string NotSameOperator::getOperatorText() {
    return "!==";
}

bool NotSameOperator::isAssignment() { return false; }

llvm::Value* NotSameOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    //1. Calculate result type
    auto targetEulType = EulType::doCommonNumberMerging(leftType, rightType, ctx);
    auto targetLlvmType = targetEulType->getLlvmType(ctx);

    //2. Cast operands, if needed
    if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
    if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = ctx->compiler->program.nativeTypes.booleanType;

     //3. Create an instruction based on the result type
    if (targetEulType->getTypeEnum() == EulTypeEnum::INT_TYPE) return ctx->builder.CreateICmpNE(left, right);
    else return ctx->builder.CreateFCmpUNE(left, right); //TODO UNE or ONE?
}
//endregion



//region EqualsOperator
int EqualsOperator::getOperatorType() {
    return yy::EulParser::token::EQUALS;
}

const std::string EqualsOperator::getOperatorText() {
    return "==";
}

bool EqualsOperator::isAssignment() { return false; }

llvm::Value* EqualsOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    //1. Calculate result type
    auto targetEulType = EulType::doCommonNumberMerging(leftType, rightType, ctx);
    auto targetLlvmType = targetEulType->getLlvmType(ctx);

    //2. Cast operands, if needed
    if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
    if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = ctx->compiler->program.nativeTypes.booleanType;

     //3. Create an instruction based on the result type
    if (targetEulType->getTypeEnum() == EulTypeEnum::INT_TYPE) return ctx->builder.CreateICmpEQ(left, right);
    else return ctx->builder.CreateFCmpUEQ(left, right); //TODO ordered or unordered?
}
//endregion


//region SameOperator
int SameOperator::getOperatorType() {
    return yy::EulParser::token::SAME;
}

const std::string SameOperator::getOperatorText() {
    return "===";
}

bool SameOperator::isAssignment() { return false; }

llvm::Value* SameOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    //1. Calculate result type
    auto targetEulType = EulType::doCommonNumberMerging(leftType, rightType, ctx);
    auto targetLlvmType = targetEulType->getLlvmType(ctx);

    //2. Cast operands, if needed
    if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
    if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = ctx->compiler->program.nativeTypes.booleanType;

     //3. Create an instruction based on the result type
    if (targetEulType->getTypeEnum() == EulTypeEnum::INT_TYPE) return ctx->builder.CreateICmpEQ(left, right);
    else return ctx->builder.CreateFCmpUEQ(left, right); //TODO ordered or unordered?
}
//endregion



//region LessOperator
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
//endregion


//region LessEqualsOperator
int LessEqualsOperator::getOperatorType() {
    return yy::EulParser::token::LESS_EQUALS;
}

const std::string LessEqualsOperator::getOperatorText() {
    return "<=";
}

bool LessEqualsOperator::isAssignment() { return false; }

llvm::Value* LessEqualsOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
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
            ctx->builder.CreateICmpULE(left, right) :
            ctx->builder.CreateICmpSLE(left, right);
    }
    else return ctx->builder.CreateFCmpULE(left, right); //TODO ordered or unordered?
}
//endregion


//region MoreOperator
int MoreOperator::getOperatorType() {
    return yy::EulParser::token::MORE;
}

const std::string MoreOperator::getOperatorText() {
    return ">";
}

bool MoreOperator::isAssignment() { return false; }

llvm::Value* MoreOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
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
            ctx->builder.CreateICmpUGT(left, right) :
            ctx->builder.CreateICmpSGT(left, right);
    }
    else return ctx->builder.CreateFCmpUGT(left, right); //TODO ordered or unordered?
}
//endregion


//region MoreEqualsOperator
int MoreEqualsOperator::getOperatorType() {
    return yy::EulParser::token::MORE_EQUALS;
}

const std::string MoreEqualsOperator::getOperatorText() {
    return ">=";
}

bool MoreEqualsOperator::isAssignment() { return false; }

llvm::Value* MoreEqualsOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
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
            ctx->builder.CreateICmpUGE(left, right) :
            ctx->builder.CreateICmpSGE(left, right);
    }
    else return ctx->builder.CreateFCmpUGE(left, right); //TODO ordered or unordered?
}
//endregion


//region NotOperator
int NotOperator::getOperatorType() {
    return yy::EulParser::token::NOT;
}

const std::string NotOperator::getOperatorText() {
    return "!";
}

bool NotOperator::isAssignment() { return false; }
//endregion




//region BinOrOperator
int BinOrOperator::getOperatorType() {
    return yy::EulParser::token::BIN_OR;
}

const std::string BinOrOperator::getOperatorText() {
    return "|";
}

bool BinOrOperator::isAssignment() { return false; }
//endregion


//region BinAndOperator
int BinAndOperator::getOperatorType() {
    return yy::EulParser::token::BIN_AND;
}

const std::string BinAndOperator::getOperatorText() {
    return "&";
}

bool BinAndOperator::isAssignment() { return false; }
//endregion


//region LeftShiftOperator
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
//endregion


//region RightShiftOperator
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
//endregion

//region PlusOperator
int PlusOperator::getOperatorType() {
    return yy::EulParser::token::PLUS;
}

const std::string PlusOperator::getOperatorText() {
    return "+";
}

bool PlusOperator::isAssignment() { return false; }

llvm::Value* PlusOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    //1. Calculate result type
    auto targetEulType = EulType::doCommonNumberMerging(leftType, rightType, ctx);
    auto targetLlvmType = targetEulType->getLlvmType(ctx);

    //2. Cast operands, if needed
    if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
    if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = targetEulType;

    //3. Create an instruction based on the result type
    if (targetEulType->getTypeEnum() == EulTypeEnum::INT_TYPE) return ctx->builder.CreateAdd(left, right);
    else return ctx->builder.CreateFAdd(left, right); //float adding
}
//endregion

//region MinusOperator
int MinusOperator::getOperatorType() {
    return yy::EulParser::token::MINUS;
}

const std::string MinusOperator::getOperatorText() {
    return "-";
}

bool MinusOperator::isAssignment() { return false; }

llvm::Value* MinusOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    //1. Calculate result type
    auto targetEulType = EulType::doCommonNumberMerging(leftType, rightType, ctx);
    auto targetLlvmType = targetEulType->getLlvmType(ctx);

    //2. Cast operands, if needed
    if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
    if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = targetEulType;


     //3. Create an instruction based on the result type
    if (targetEulType->getTypeEnum() == EulTypeEnum::INT_TYPE) return ctx->builder.CreateSub(left, right);
    else return ctx->builder.CreateFSub(left, right); //float adding
}
//endregion


//region PercentOperator
int PercentOperator::getOperatorType() {
    return yy::EulParser::token::PERCENT;
}

const std::string PercentOperator::getOperatorText() {
    return "%";
}

bool PercentOperator::isAssignment() { return false; }

llvm::Value* PercentOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    //1. Calculate result type
    auto targetEulType = EulType::doCommonNumberMerging(leftType, rightType, ctx);
    auto targetLlvmType = targetEulType->getLlvmType(ctx);

    //2. Cast operands, if needed
    if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
    if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = targetEulType;

     //3. Create an instruction based on the result type
     if (targetEulType->getTypeEnum() == EulTypeEnum::INT_TYPE) {
        auto asInt = static_cast<EulIntegerType*>(targetEulType.get());
        return asInt->isUnsigned?
                ctx->builder.CreateURem(left, right) :
                ctx->builder.CreateSRem(left, right);
     }
     else return ctx->builder.CreateFRem(left, right);
}
//endregion

//region StarOperator
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
//endregion

//region SlashOperator
int SlashOperator::getOperatorType() {
    return yy::EulParser::token::SLASH;
}

const std::string SlashOperator::getOperatorText() {
    return "/";
}

bool SlashOperator::isAssignment() { return false; }

llvm::Value* SlashOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    //1. Calculate result type
    auto targetEulType = EulType::doCommonNumberMerging(leftType, rightType, ctx);
    auto targetLlvmType = targetEulType->getLlvmType(ctx);

    //2. Cast operands, if needed
    if (targetLlvmType != left->getType()) left = targetEulType->castValue(left, leftType.get(), false, ctx);
    if (targetLlvmType != right->getType()) right = targetEulType->castValue(right, rightType.get(), false, ctx);
    *resultTypeAddr = targetEulType;

    //3. Create an instruction based on the result type
    if (targetEulType->getTypeEnum() == EulTypeEnum::INT_TYPE) {
        auto asInt = static_cast<EulIntegerType*>(targetEulType.get());
        return asInt->isUnsigned?
            ctx->builder.CreateUDiv(left, right) :
            ctx->builder.CreateSDiv(left, right);
    }
    else return ctx->builder.CreateFDiv(left, right);
}
//endregion


//region TildeOperator
int TildeOperator::getOperatorType() {
    return yy::EulParser::token::TILDE;
}

const std::string TildeOperator::getOperatorText() {
    return "~";
}

bool TildeOperator::isAssignment() { return false; }
//endregion


//region DecreaseOperator
int DecreaseOperator::getOperatorType() {
    return yy::EulParser::token::DECREASE;
}

const std::string DecreaseOperator::getOperatorText() {
    return "--";
}

bool DecreaseOperator::isAssignment() { return true; }
//endregion


//region IncreaseOperator
int IncreaseOperator::getOperatorType() {
    return yy::EulParser::token::INCREASE;
}

const std::string IncreaseOperator::getOperatorText() {
    return "++";
}

bool IncreaseOperator::isAssignment() { return true; }
//endregion


//region DotOperator
int DotOperator::getOperatorType() {
    return yy::EulParser::token::DOT;
}

const std::string DotOperator::getOperatorText() {
    return ".";
}

bool DotOperator::isAssignment() { return false; }
//endregion


//region QuestionOperator
int QuestionOperator::getOperatorType() {
    return yy::EulParser::token::QUESTION;
}

const std::string QuestionOperator::getOperatorText() {
    return "?";
}

bool QuestionOperator::isAssignment() { return false; }
//endregion


//region ColonOperator
int ColonOperator::getOperatorType() {
    return yy::EulParser::token::COLON;
}

const std::string ColonOperator::getOperatorText() {
    return ":";
}

bool ColonOperator::isAssignment() { return false; }
//endregion


/** Define the global context that includes all operators */
EulOperators EUL_OPERATORS;
