#pragma once

/**
    This class represents an int token. Ints in EUL have a size, and can be signed or unsigned.
*/
class EulIntToken : public EulToken {
    //region FIELDS
    public: unsigned long int value;
    public: unsigned char size; //in bits
    public: char isUnsigned;
    //endregion




    //region LIFE CYCLE
    public: EulIntToken(char* text);
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    public: virtual EulTokenType getType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx);
    public: llvm::Type* generateType(EulCodeGenContext* ctx);
};