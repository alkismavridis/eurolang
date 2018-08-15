#pragma once

/**
    This class represents a string token.
*/
class EulStringToken : public EulToken {
    //region FIELDS
    public: std::string value;
    //endregion




    //region LIFE CYCLE
    public: EulStringToken(const std::string& buf);
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion


    public: virtual EulTokenType getType();
    public: llvm::Type* generateType(EulCodeGenContext* ctx);
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
};