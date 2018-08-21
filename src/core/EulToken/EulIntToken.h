#pragma once

/**
    This class represents an int token. Ints in EUL have a size, and can be signed or unsigned.
*/
class EulIntToken : public EulToken {
    //region FIELDS
    public: unsigned long int value;
    public: unsigned char size; //in bits
    public: bool isUnsigned;
    //endregion




    //region LIFE CYCLE
    public: EulIntToken(char* text);
    public: EulIntToken(unsigned long int value, unsigned char size, bool isUnsigned);
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    public: virtual EulTokenType getType();
    public: virtual std::shared_ptr<EulType> getEulType(EulCodeGenContext* ctx, unsigned int someParam);
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
};