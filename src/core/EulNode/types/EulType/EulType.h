#pragma once


//region UGGLY FORWARD DECLARATIONS
class EulIntegerType;
class EulFloatType;
//endregion


/**
    A wrapper class to return llvm types.
    This class is abstract, please refer to sub classes for implementations.
    NOTE an EulType can exist before any llvm context is initialized.
*/
class EulType : public EulNode {
    //region STATIC UTILS
    public: static std::shared_ptr<EulIntegerType> doCommonIntMerging(std::shared_ptr<EulType> left, std::shared_ptr<EulType> right, EulCodeGenContext* ctx);
    public: static std::shared_ptr<EulFloatType> doCommonFloatMerging(std::shared_ptr<EulType> left, std::shared_ptr<EulType> right, EulCodeGenContext* ctx);
    public: static std::shared_ptr<EulType> doCommonNumberMerging(std::shared_ptr<EulType> left, std::shared_ptr<EulType> right, EulCodeGenContext* ctx);

    public: virtual llvm::Value* castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx);
    //endregion



    //region CLASS HIERARCHY UTILSs
    public: EulNodeType getNodeType();
    public: static bool isEulType(EulNode* tok);
    //endregion


    public: virtual EulTypeEnum getTypeEnum();
    public: std::shared_ptr<EulType> getPointerTo(unsigned char depth = 1);



    //region LLVM
    public: virtual llvm::Type* getLlvmType(EulCodeGenContext* ctx);
    //endregion

};
