#pragma once

/**
    Any type represents a type that can represent any other type,
    and thus no value casting is required when one performs a type casting
    from an other type towards Any.
*/
class EulAnyType : public EulType {
    //region LIFE CYCLE
    public: EulAnyType();
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