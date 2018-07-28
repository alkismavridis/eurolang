#pragma once


class Compiler;



/**
    This represents a char token. Chars in eul can have various sizes, just like ints.
*/
class EulCharToken : public EulToken {
    //region FIELDS
    public: unsigned long int value;
    public: unsigned char size; //in bytes
    //endregion




    //region LIFE CYCLE
    public: EulCharToken(unsigned long int value, unsigned char size);
    public: EulCharToken(const char* text, unsigned int len, Compiler* compiler);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion




    public: virtual EulTokenType getType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx);
    public: llvm::Type* generateType(EulCodeGenContext* ctx);
};