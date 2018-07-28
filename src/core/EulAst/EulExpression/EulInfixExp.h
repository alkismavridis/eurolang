#pragma once

class EulInfixExp : public EulExpression {
    //region LIFE CYCLE
    public: EulToken* left;
    public: EulOperator* oper;
    public: EulToken* right;
    //endregion



    //region LIFE CYCLE
    public: EulInfixExp(EulToken* left, EulOperator* oper, EulToken* right);
    public: ~EulInfixExp();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx);
    //endregion
};