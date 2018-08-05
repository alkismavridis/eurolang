#pragma once

class EulTokenExp : public EulExpression {
    //region LIFE CYCLE
    public:std::shared_ptr<EulToken> token;
    //endregion



    //region LIFE CYCLE
    public: EulTokenExp(std::shared_ptr<EulToken> token);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx);
    //endregion
};