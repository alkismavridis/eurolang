#pragma once

class EulStatement : public EulNode {
    public: virtual EulStatementType getStatementType();
    public: virtual void generateStatement(EulCodeGenContext* ctx);
    public: virtual EulNodeType getNodeType();

    /**
        This function is called during code generation. It ensures that the statement will be reachable.
        Unlike, for example return 0; i++;
    */
    public: static void assertStatementReachable(EulCodeGenContext* ctx);
    public: virtual void performPreParsing(EulCodeGenContext* ctx);
};
