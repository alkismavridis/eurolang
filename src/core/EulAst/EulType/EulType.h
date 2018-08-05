#pragma once

/**
    This is a wrapper object for an llvm::Type*
    The reason that we need a wrapper is because a Type may be not-yet-defined when it is requested.
    There will be no forward declarations in eurolang.
*/
class EulType : public EulAst {
    //region FIELDS
    public: std::shared_ptr<EulIdToken> llvmTypeName;
    //endregion



    //region LIFE CYCLE
    public: EulType(std::shared_ptr<EulIdToken> llvmTypeName);
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion


    //region OVERRIDES
    public: EulAstType getAstType();
    //endregion


    public: static bool isEulType(EulToken* tok);
};