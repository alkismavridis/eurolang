#pragma once

/**
    This is a wrapper object for an llvm::Type*
    The reason that we need a wrapper is because a Type may be not-yet-defined when it is requested.
    There will be no forward declarations in eurolang.
*/
class EulType : public EulAst {
    //region FIELDS
    public: llvm::Type* llvmType;
    //endregion



    //region LIFE CYCLE
    public: EulType(llvm::Type* type);
    public: virtual ~EulType();
    //endregion



    //region GETTERS
    public: virtual bool isLateDeclared();
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: EulAstType getAstType();
    //endregion


    public: static bool isEulType(EulToken* tok);
};