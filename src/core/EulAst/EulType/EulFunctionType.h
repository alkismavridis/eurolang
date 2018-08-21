#pragma once

/**
    This is a wrapper object for an llvm::Type*
    The reason that we need a wrapper is because a Type may be not-yet-defined when it is requested.
    There will be no forward declarations in eurolang.
*/
class EulFunctionType : public EulType {
    //region FIELDS
    public: std::shared_ptr<EulType> retType;
    public: std::vector<std::shared_ptr<EulType>> argTypes;
    //endregion



    //region LIFE CYCLE
    public: EulFunctionType(const std::shared_ptr<EulType> retType);
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: virtual EulTypeEnum getTypeEnum();
    public: virtual llvm::Type* getLlvmType(EulCodeGenContext* ctx);
    //endregion
};