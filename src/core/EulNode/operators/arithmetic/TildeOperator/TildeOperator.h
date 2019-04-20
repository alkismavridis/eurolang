#pragma once


class TildeOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};
