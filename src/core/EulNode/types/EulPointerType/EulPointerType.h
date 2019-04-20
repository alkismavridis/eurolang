#pragma once

/**
    This represents a pointer to an other type.
    It can be also a pointer to a pointer to a type etc.
    The number of "pointers to" are represented by the depth property.
*/
class EulPointerType : public EulType {
    //region FIELDS
    public: unsigned char depth;
    public: EulType* contentType;
    //endregion



    //region LIFE CYCLE
    public: EulPointerType(EulType* type, unsigned char depth = 1);
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: virtual EulTypeEnum getTypeEnum();
    public: virtual llvm::Type* getLlvmType(EulCodeGenContext* ctx);
    public: virtual llvm::Value* castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx);
    //endregion
};