#pragma once

class EulInfixExp : public EulExpression {
    //region LIFE CYCLE
    public: EulToken* left;
    public: int operatorType;
    public: EulToken* right;
    //endregion



    //region LIFE CYCLE
    public: EulInfixExp(EulToken* left, int operatorType, EulToken* right);
    public: ~EulInfixExp();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenerator* gen);
    //endregion
};