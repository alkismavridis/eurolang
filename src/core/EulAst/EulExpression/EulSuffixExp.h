#pragma once

class EulSuffixExp : public EulExpression {
    //region LIFE CYCLE
    public: std::shared_ptr<EulToken> exp;
    public: EulOperator* oper;
    //endregion



    //region LIFE CYCLE
    public: EulSuffixExp(std::shared_ptr<EulToken> exp, EulOperator* oper);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
    //endregion
};