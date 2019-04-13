#pragma once

class EulPrefixExp : public EulExpression {
    //region LIFE CYCLE
    public: std::shared_ptr<EulNode> exp;
    public: EulOperator* oper;
    //endregion



    //region LIFE CYCLE
    public: EulPrefixExp(EulOperator* oper, std::shared_ptr<EulNode> exp);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
    //endregion
};
