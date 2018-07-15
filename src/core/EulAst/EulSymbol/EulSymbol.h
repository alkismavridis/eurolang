#pragma once

class EulSymbol : public EulAst {
    //region FIELDS
    public: int changeType; //one of yy::EulParser::token
    public: EulType* varType;
    public: EulToken* value;
    public: char destroyContent;
    //endregion



    //region LIFE CYCLE
    public: EulSymbol(int changeType, EulType* varType, EulToken* value, char destroyContent);
    public: virtual ~EulSymbol();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulAstType getAstType();
    //endregion
};