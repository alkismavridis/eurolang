#pragma once


class EulExpression : public ValueNode {
    //region FIELDS
    /**
        every expression has a compile time type.
        Please note that this type is calculated during the parsing of the AST
        by the code generator.
        It is NOT available during the building of the AST. So, assume that it is null at this point.
    */
    public: std::shared_ptr<EulType> compileTimeType = nullptr;
    //endregion


    public: virtual EulExpressionType getExpressionType();
    public: virtual EulNodeType getNodeType();


    //region OVERRIDES
    public: virtual bool isSymbolId();
    public: std::shared_ptr<EulType> getEulType(EulCodeGenContext* ctx, unsigned int someParam);
    //endregion
};
