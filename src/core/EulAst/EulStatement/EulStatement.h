#pragma once

class EulStatement {
    public: EulStatementType getStatementType();
    public: EulAstType getAstType() { return STATEMENT; }
};