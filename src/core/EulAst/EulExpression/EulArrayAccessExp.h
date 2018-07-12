#pragma once

class EulArrayAccessExp : public EulExpression {
    //region LIFE CYCLE
    public: EulToken* obj;
    public: EulToken* index;
    //endregion



    //region LIFE CYCLE
    public: EulArrayAccessExp(EulToken* obj, EulToken* index);
    public: ~EulArrayAccessExp();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulExpressionType getExpressionType();
    //endregion
};