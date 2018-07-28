#pragma once

class EulSuffixExp : public EulExpression {
    //region LIFE CYCLE
    public: EulToken* exp;
    public: EulOperator* oper;
    //endregion



    //region LIFE CYCLE
    public: EulSuffixExp(EulToken* exp, EulOperator* oper);
    public: virtual ~EulSuffixExp();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx);
    //endregion
};