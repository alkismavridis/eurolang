#pragma once

/**
    This class represents an int token. Ints in EUL have a size, and can be signed or unsigned.
*/
class EulBooleanToken : public EulToken {
    //region FIELDS
    public: bool value;
    //endregion




    //region LIFE CYCLE
    public: EulBooleanToken(bool value);
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    public: virtual EulTokenType getType();
    public: virtual std::shared_ptr<EulType> getEulType(EulCodeGenContext* ctx, unsigned int someParam);
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
};