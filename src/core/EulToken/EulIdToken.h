#pragma once

/**
    This class represents an ID token, like a variable name or a method.
*/
class EulIdToken : public EulToken {
    //region FIELDS
    public: std::string name;
    public: EulScope* scope;
    //endregion




    //region LIFE CYCLE
    public: EulIdToken(const char* text, unsigned int length, EulScope* scope);
    public: EulIdToken(const std::string& name, EulScope* scope);
    //endregion




    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    public: virtual EulTokenType getType();
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
};