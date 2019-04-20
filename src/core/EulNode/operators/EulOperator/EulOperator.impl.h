#pragma once



//region BASE CLASS
llvm::Value* EulOperator::performPrefix(llvm::Value* arg, std::shared_ptr<EulType> argType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::performPrefix was called, but should not.");
}

llvm::Value* EulOperator::performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::performInfix was called, but should not.");
}

llvm::Value* EulOperator::assignInfix(EulSymbol* symbol, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::assignInfix was called, but should not.");
}

llvm::Value* EulOperator::performSuffix(llvm::Value* arg, std::shared_ptr<EulType> argType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx) {
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




/** Define the global context that includes all operators */
EulOperators EUL_OPERATORS;
