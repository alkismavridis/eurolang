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




    public: virtual EulTokenType getType();
};