#pragma once

class EulArrayAccessExp : public EulExpression {
    //region LIFE CYCLE
    public: std::shared_ptr<ValueNode> obj;
    public: std::shared_ptr<ValueNode> index;
    //endregion



    //region LIFE CYCLE
    public: EulArrayAccessExp(std::shared_ptr<ValueNode> obj, std::shared_ptr<ValueNode> index);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
    //endregion
};
