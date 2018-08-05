#pragma once

class VarDeclaration : public EulAst {
    //region FIELDS
    public: std::shared_ptr<EulIdToken> id;
    public: std::shared_ptr<EulType> varType;
    public: std::shared_ptr<EulToken> value; //either an expression or a IntToken, CharToken etc.
    //endregion



    //region LIFE CYCLE
    public: VarDeclaration(std::shared_ptr<EulIdToken> id, std::shared_ptr<EulType> varType, std::shared_ptr<EulToken>);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion




    //region OVERRIDES
    public: EulAstType getAstType();
    //endregion



    //region CODE GENERATOR
    public: llvm::Type* generateType(EulCodeGenContext* ctx);
    //endregion
};