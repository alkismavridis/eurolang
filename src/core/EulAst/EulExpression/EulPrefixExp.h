#pragma once

class EulPrefixExp : public EulExpression {
    //region LIFE CYCLE
    public: EulToken* exp;
    public: EulOperator* oper;
    //endregion



    //region LIFE CYCLE
    public: EulPrefixExp(EulOperator* oper, EulToken* exp);
    public: virtual ~EulPrefixExp();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx);
    //endregion
};