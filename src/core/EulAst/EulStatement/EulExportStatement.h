#pragma once

class EulExportStatement {




    //region OVERRIDES
    public: EulStatementType getStatementType() { return EXPORT; }
    public: EulAstType getAstType() { return STATEMENT; }
    //endregion
};