#pragma once

class EulSymbol : public EulAst {
    //region FIELDS
    public: int changeType; //one of yy::EulParser::token
    public: std::string name;
    public: EulType* varType;
    public: EulToken* value;
    //endregion



    //region LIFE CYCLE
    public: EulSymbol(int changeType, const std::string& name, EulType* varType, EulToken* value);
    public: virtual ~EulSymbol();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulAstType getAstType();
    //endregion
};