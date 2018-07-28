#pragma once

class EulStatement : public EulAst {
    public: virtual EulStatementType getStatementType();
    public: EulAstType getAstType();
    public: virtual void generateStatement(EulCodeGenContext* ctx);
};