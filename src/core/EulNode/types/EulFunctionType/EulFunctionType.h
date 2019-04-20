#pragma once

class VarDeclaration;

class EulFunctionType : public EulType {
    //region FIELDS
    public: std::shared_ptr<EulType> retType;
    public: std::vector<std::shared_ptr<EulType>> argTypes; //This vector does NOT include var args.
    public: std::shared_ptr<EulType> varArgsType; //may be null. if the function does not have var arg parameters
    //endregion



    //region LIFE CYCLE
    public: EulFunctionType(const std::shared_ptr<EulType> retType);
    public: EulFunctionType(
        const std::shared_ptr<EulType> retType,
        std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> argDeclarations
    );

    public: EulFunctionType(
        const std::shared_ptr<EulType> retType,
        std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> argDeclarations,
        const std::shared_ptr<EulType> varArgType
    );
    //endregion


    //region MISC
    public: virtual void toJson(std::ostream& out, int tabs);

    /** Determines whether the function cam be called with the given number of parameters. */
    public: bool isParameterCountValid(unsigned int paramCount);
    //endregion



    //region OVERRIDES
    public: virtual EulTypeEnum getTypeEnum();
    public: virtual llvm::Type* getLlvmType(EulCodeGenContext* ctx);
    public: virtual llvm::Value* castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx);
    //endregion
};