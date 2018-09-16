#pragma once

/**
    This describes a function declaration (including its block).
*/
class EulFuncDeclarationStatement : public EulStatement {
    //region FIELDS
    public: std::shared_ptr<EulFunction> func;
    public: std::shared_ptr<EulIdToken> name;
    public: llvm::Function* llvmFunc;
    //endregion



    //region LIFE CYCLE
    public: EulFuncDeclarationStatement(std::shared_ptr<EulFunction> func, std::shared_ptr<EulIdToken> name);
    //endregion



    //region MISC
    public: virtual void toJson(std::ostream& out, int tabs);
    public: EulStatementType getStatementType();
    //endregion


    //region CODE GENERATION
    public: void generateStatement(EulCodeGenContext* ctx);
    public: void performPreParsing(EulCodeGenContext* ctx);
    //endregion
};