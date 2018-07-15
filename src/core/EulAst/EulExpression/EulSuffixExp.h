#pragma once

class EulSuffixExp : public EulExpression {
    //region LIFE CYCLE
    public: EulToken* exp;
    public: int operatorType;
    //endregion



    //region LIFE CYCLE
    public: EulSuffixExp(EulToken* exp, int operatorType);
    public: virtual ~EulSuffixExp();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenerator* gen);
    //endregion
};