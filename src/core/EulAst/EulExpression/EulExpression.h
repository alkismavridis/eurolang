#pragma once

class EulExpression : public EulStatement {
    //region OVERRIDES
    public: EulAstType getAstType();
    public: virtual EulExpressionType getExpressionType();
    //endregion
};