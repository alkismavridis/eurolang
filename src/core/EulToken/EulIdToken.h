#pragma once

/**
    This class represents an ID token, like a variable name or a method.
*/
class EulIdToken : public EulToken {
    //region FIELDS
    public: std::string name;
    //endregion




    //region LIFE CYCLE
    public: EulIdToken(std::string* name);
    public: EulIdToken(const char* name, unsigned int length);
    //endregion




    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    public: virtual EulTokenType getType();
    public: llvm::Value* generateValue(EulCodeGenerator* gen);
};