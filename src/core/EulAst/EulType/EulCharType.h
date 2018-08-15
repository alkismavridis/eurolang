#pragma once

/**
    This is a wrapper object for an llvm::Type*
    The reason that we need a wrapper is because a Type may be not-yet-defined when it is requested.
    There will be no forward declarations in eurolang.
*/
class EulCharType : public EulType {
    //region FIELDS
    public: unsigned char size; //in bits
    //endregion



    //region LIFE CYCLE
    public: EulCharType(unsigned char size);
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: virtual llvm::Type* getLlvmType(EulCodeGenContext* ctx);
    public: virtual EulTypeEnum getTypeEnum();
    //endregion
};