#pragma once

/**
    EulExpStatement stands for Eul Expression Statement.
    This is a statement that is made of one Expression, like a function call or an assignment.
*/
class EulExpStatement : public EulStatement {
    //region FIELDS
    public: std::shared_ptr<EulToken> exp;
    //endregion



    //region LIFE CYCLE
    public: EulExpStatement(std::shared_ptr<EulToken> exp);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion




    //region OVERRIDES
    public: EulStatementType getStatementType();
    public: void generateStatement(EulCodeGenContext* ctx);
    //endregion
};