#pragma once

class EulImportStatement {
    //region OVERRIDES
    public: EulStatementType getStatementType() { return IMPORT; }
    public: EulAstType getAstType() { return STATEMENT; }
    //endregion
};