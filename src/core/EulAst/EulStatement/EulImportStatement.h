#pragma once

class EulImportStatement : public EulStatement{
    //region OVERRIDES
    public: EulStatementType getStatementType();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion
};