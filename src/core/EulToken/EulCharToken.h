#pragma once


class Compiler;




/**
    This represents a char token. Chars in eul can have various sizes, just like ints.
*/
class EulCharToken : public EulToken {
    //region FIELDS
    public: unsigned long long int value;
    public: unsigned char size; //in bytes
    //endregion




    //region LIFE CYCLE
    public: EulCharToken(unsigned long int value, unsigned char size);
    public: EulCharToken(const char* text, unsigned int len, Compiler* compiler);
    //endregion




    public: virtual EulTokenType getType();
};