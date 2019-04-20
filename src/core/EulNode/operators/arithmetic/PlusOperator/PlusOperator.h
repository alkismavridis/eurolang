#pragma once


class PlusOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);

    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};
