#pragma once

class EulFunctionCallExp : public EulExpression {
    //region LIFE CYCLE
    public: EulToken* func;
    public: std::vector<EulToken*>* params;  //NOTE: If function call has no parameters, like sayHello(), params will be null
    //endregion



    //region LIFE CYCLE
    public: EulFunctionCallExp(EulToken* func, std::vector<EulToken*>* params);
    public: ~EulFunctionCallExp();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenerator* gen);
    //endregion
};