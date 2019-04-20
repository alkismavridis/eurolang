#pragma once

class EulOperator {
    public: virtual llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> argType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);


    public: virtual llvm::Value* performInfix(
        llvm::Value* left,  //the left value
        std::shared_ptr<EulType> leftType,  //the compile time type of the left value
        llvm::Value* right,                 //the right value
        std::shared_ptr<EulType> rightType, //the compile time type of the right value
        std::shared_ptr<EulType>* resultTypeAddress,    //we must store the result compile-time type here
        EulCodeGenContext* ctx
    );

    /** same as performInfix, but it accepts a symbol instead of a value as left operand, in order to perform assignments. */
    public: virtual llvm::Value* assignInfix(
        EulSymbol* sym,                     //the symbol to assign to
        llvm::Value* right,                 //the right value
        std::shared_ptr<EulType> rightType, //the compile time type of the right value
        std::shared_ptr<EulType>* resultTypeAddress,    //we must store the result compile-time type here
        EulCodeGenContext* ctx
    );


    public: virtual llvm::Value* performSuffix(llvm::Value* arg, std::shared_ptr<EulType> argType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);

    public: virtual int getOperatorType();
    public: virtual const std::string getOperatorText();
    public: virtual bool isAssignment();
};
