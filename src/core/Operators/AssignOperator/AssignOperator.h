#pragma once

class AssignOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();

    public: llvm::Value* assignInfix(EulSymbol* symbol, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
    public: bool isAssignment();
};
