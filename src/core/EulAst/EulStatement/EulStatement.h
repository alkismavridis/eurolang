#pragma once

class EulStatement : public EulAst {
    public: virtual EulStatementType getStatementType();
    public: EulAstType getAstType();
};