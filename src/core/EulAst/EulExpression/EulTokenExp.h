#pragma once

class EulTokenExp : public EulExpression {
    //region LIFE CYCLE
    public:EulToken* token;
    //endregion



    //region LIFE CYCLE
    public: EulTokenExp(EulToken* token);
    public: virtual ~EulTokenExp();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx);
    //endregion
};