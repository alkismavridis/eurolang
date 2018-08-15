#pragma once

/**
    This class represents a float token. Floats in EUL have a size.
*/
class EulFloatToken : public EulToken {
    //region FIELDS
    public: double value;
    public: unsigned char size; //in bytes
    //endregion




    //region LIFE CYCLE
    public: EulFloatToken(double value, unsigned char size);
    public: EulFloatToken(char* text);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion


    public: virtual EulTokenType getType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
    public: llvm::Type* generateType(EulCodeGenContext* ctx);
};