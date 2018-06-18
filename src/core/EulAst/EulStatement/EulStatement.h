#pragma once

class EulStatement : public EulAst {
    public: EulStatementType getStatementType();
    public: EulAstType getAstType();
};