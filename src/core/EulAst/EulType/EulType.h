#pragma once

/**
    A wrapper class to return llvm types.
    This class is abstract, please refer to sub classes for implementations.
    NOTE an EulType can exist before any llvm context is initialized.
*/
class EulType : public EulAst {
    //region FIELDS
    //endregion



    //region CLASS HIERARCHY UTILSs
    public: EulAstType getAstType();
    public: static bool isEulType(EulToken* tok);
    //endregion


    public: virtual EulTypeEnum getTypeEnum();



    //region LLVM
    public: virtual llvm::Type* getLlvmType(EulCodeGenContext* ctx);
    //endregion

};