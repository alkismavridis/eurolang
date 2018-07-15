#pragma once

/**
    EulExpStatement stands for Eul Expression Statement.
    This is a statement that is made of one Expression, like a function call or an assignment.
*/
class EulExpStatement : public EulStatement {
    //region FIELDS
    public: EulToken* exp; //one of yy::EulParser::token
    //endregion



    //region LIFE CYCLE
    public: EulExpStatement(EulToken* exp);
    public: virtual ~EulExpStatement();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion




    //region OVERRIDES
    public: EulStatementType getStatementType();
    public: void generateCode(EulCodeGenerator* gen);
    //endregion
};