#pragma once

class NotOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> argType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};
