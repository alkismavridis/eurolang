#pragma once

class VarDeclaration;

class EulFunctionType : public EulType {
    //region FIELDS
    public: std::shared_ptr<EulType> retType;
    public: std::vector<std::shared_ptr<EulType>> argTypes;
    //endregion



    //region LIFE CYCLE
    public: EulFunctionType(const std::shared_ptr<EulType> retType);
    public: EulFunctionType(const std::shared_ptr<EulType> retType, std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> argDeclarations);
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