#pragma once

class EulExpression : public EulStatement {
    //region FIELDS
    /**
        every expression has a compile time type.
        Please note that this type is calculated during the parsing of the AST
        by the code generator.
        It is NOT available during the building of the AST. So, assume that it is null at this point.
    */
    public: std::shared_ptr<EulType> compileTimeType = nullptr;
    //endregion


    //region OVERRIDES
    public: EulAstType getAstType();
    public: std::shared_ptr<EulType> getEulType(EulCodeGenContext* ctx, unsigned int someParam);
    public: virtual EulExpressionType getExpressionType();
    //endregion
};