#pragma once

class EqualsOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};
