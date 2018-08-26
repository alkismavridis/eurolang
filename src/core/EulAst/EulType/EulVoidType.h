#pragma once

class EulVoidType : public EulType {
    //region LIFE CYCLE
    public: EulVoidType() {}
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