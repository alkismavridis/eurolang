#pragma once


class VarDeclarationStatement : public EulStatement {
    //region FIELDS
    public: int varType; //one of yy::EulParser::token
    public: std::vector<std::shared_ptr<VarDeclaration>>* declarations;
    //endregion



    //region LIFE CYCLE
    public: VarDeclarationStatement(int varType, std::vector<std::shared_ptr<VarDeclaration>>* declarations);
    public: virtual ~VarDeclarationStatement();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion




    //region OVERRIDES
    public: EulStatementType getStatementType();
    public: void generateStatement(EulCodeGenContext* ctx);
    //endregion
};