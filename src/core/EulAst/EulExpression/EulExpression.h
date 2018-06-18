#pragma once

class EulExpression : public EulAst {
    //region OVERRIDES
    public: EulAstType getAstType();
    public: virtual EulExpressionType getExpressionType();
    //endregion
};