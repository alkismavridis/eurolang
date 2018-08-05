#pragma once

class EulFunctionCallExp : public EulExpression {
    //region LIFE CYCLE
    public: std::shared_ptr<EulToken> func;
    public: std::vector<std::shared_ptr<EulToken>>* params;  //NOTE: If function call has no parameters, like sayHello(), params will be null
    //endregion



    //region LIFE CYCLE
    public: EulFunctionCallExp(std::shared_ptr<EulToken> func, std::vector<std::shared_ptr<EulToken>>* params);
    public: ~EulFunctionCallExp();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx);
    //endregion
};