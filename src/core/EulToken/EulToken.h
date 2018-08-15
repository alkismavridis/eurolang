
#pragma once

/**
    This is the base class of all tokens. It only provides a getType() method, which will determine if this token
    is an Operator token, an Integer token and so on.
*/
class EulToken {
    public: virtual ~EulToken();
    public: virtual EulTokenType getType();


    //region CODE GENERATION
    public: virtual llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
    public: virtual llvm::Type* generateType(EulCodeGenContext* ctx);
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    public: static void toJson(std::ostream& out, std::vector<EulToken*>* tokens, int tabs);
    //endregion
};

std::ostream& operator<<(std::ostream& os, EulToken* tok);
