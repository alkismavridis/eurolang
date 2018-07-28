#pragma once


class ReturnStatement : public EulStatement {
    //region FIELDS
    public: EulToken* exp; //can be null in case of void
    //endregion



    //region LIFE CYCLE
    public: ReturnStatement(EulToken* exp);
    public: virtual ~ReturnStatement();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion




    //region OVERRIDES
    public: EulStatementType getStatementType();
    public: void generateStatement(EulCodeGenContext* ctx);
    //endregion
};