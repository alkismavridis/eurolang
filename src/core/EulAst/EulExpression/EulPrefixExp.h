#pragma once

class EulPrefixExp : public EulExpression {
    //region LIFE CYCLE
    public: EulToken* exp;
    public: int operatorType;
    //endregion



    //region LIFE CYCLE
    public: EulPrefixExp(int operatorType, EulToken* exp);
    public: virtual ~EulPrefixExp();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenerator* gen);
    //endregion
};