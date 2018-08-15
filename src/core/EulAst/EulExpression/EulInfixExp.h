#pragma once

class EulInfixExp : public EulExpression {
    //region LIFE CYCLE
    public: std::shared_ptr<EulToken> left;
    public: EulOperator* oper;
    public: std::shared_ptr<EulToken> right;
    //endregion



    //region LIFE CYCLE
    public: EulInfixExp(std::shared_ptr<EulToken> left, EulOperator* oper, std::shared_ptr<EulToken> right);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
    //endregion
};