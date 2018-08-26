#pragma once


class EulNativeTypes {
    //region FIELDS
    public: std::shared_ptr<EulVoidType> voidType;

    public: std::shared_ptr<EulIntegerType> int8Type;
    public: std::shared_ptr<EulIntegerType> int16Type;
    public: std::shared_ptr<EulIntegerType> int32Type;
    public: std::shared_ptr<EulIntegerType> int64Type;
    public: std::shared_ptr<EulIntegerType> intType;

    public: std::shared_ptr<EulIntegerType> uint8Type;
    public: std::shared_ptr<EulIntegerType> uint16Type;
    public: std::shared_ptr<EulIntegerType> uint32Type;
    public: std::shared_ptr<EulIntegerType> uint64Type;
    public: std::shared_ptr<EulIntegerType> uintType;

    public: std::shared_ptr<EulFloatType> float32Type;
    public: std::shared_ptr<EulFloatType> float64Type;
    public: std::shared_ptr<EulFloatType> floatType;

    public: std::shared_ptr<EulCharType> char8Type;
    public: std::shared_ptr<EulCharType> char16Type;
    public: std::shared_ptr<EulCharType> char32Type;
    public: std::shared_ptr<EulCharType> charType;

    public: std::shared_ptr<EulStringType> stringType;
    public: std::shared_ptr<EulBooleanType> booleanType;
    //endregion


    public: EulNativeTypes();
};