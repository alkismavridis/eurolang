#pragma once

class EulStatement : public EulAst {
    public: virtual EulStatementType getStatementType();
    public: EulAstType getAstType();
    public: virtual void generateStatement(EulCodeGenContext* ctx);

    /**
        This function is called during code generation. It ensures that the statement will be reachable.
        Unlike, for example return 0; i++;
    */
    public: static void assertStatementReachable(EulCodeGenContext* ctx);
    public: virtual void performPreParsing(EulCodeGenContext* ctx);
};