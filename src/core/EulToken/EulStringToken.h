#pragma once

/**
    This class represents a string token.
*/
class EulStringToken : public EulToken {
    //region FIELDS
    public: std::string value;
    //endregion




    //region LIFE CYCLE
    public: EulStringToken(std::string& buf);
    //endregion




    public: virtual EulTokenType getType();
};