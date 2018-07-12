#pragma once

class EulType : public EulAst {
    //region FIELDS
    public: std::string name;
    //endregion



    //region LIFE CYCLE
    public: EulType(const std::string& name);
    public: virtual ~EulType();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulAstType getAstType();
    //endregion
};