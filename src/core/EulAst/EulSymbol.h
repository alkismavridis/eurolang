#pragma once

class EulSymbol {
    //region FIELDS
    public: std::string name;
    //endregion




    //region LIFE CYCLE
    public: EulSymbol(char* id);
    public: ~EulSymbol();
    //endregion




    //region OVERRIDES
    public: EulAstType getAstType() { return SYMBOL; }
    //endregion
};