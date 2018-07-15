#pragma once


class VarDeclarationStatement : public EulStatement {
    //region FIELDS
    public: int varType; //one of yy::EulParser::token
    public: std::vector<VarDeclaration*>* declarations;
    //endregion



    //region LIFE CYCLE
    public: VarDeclarationStatement(int varType, std::vector<VarDeclaration*>* declarations);
    public: virtual ~VarDeclarationStatement();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion




    //region OVERRIDES
    public: EulStatementType getStatementType();
    public: void generateCode(EulCodeGenerator* gen);
    //endregion
};