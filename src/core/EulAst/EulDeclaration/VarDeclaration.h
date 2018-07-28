#pragma once

class VarDeclaration : public EulAst {
    //region FIELDS
    public: EulIdToken* id;
    public: EulType* varType;
    public: EulToken* value; //either an expression or a IntToken, CharToken etc.
    //endregion



    //region LIFE CYCLE
    public: VarDeclaration(EulIdToken* id, EulType* varType, EulToken* value);
    public: virtual ~VarDeclaration();
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