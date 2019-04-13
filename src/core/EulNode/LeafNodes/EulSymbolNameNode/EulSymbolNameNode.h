#pragma once

/**
    This class represents an ID token, like a variable name or a method.
*/
class EulSymbolNameNode : public EulNode {
    //region FIELDS
    public: std::string name;
    public: std::shared_ptr<EulScope> scope;
    //endregion




    //region LIFE CYCLE
    public: EulSymbolNameNode(const char* text, unsigned int length, std::shared_ptr<EulScope> scope);
    public: EulSymbolNameNode(const std::string& name, std::shared_ptr<EulScope> scope);
    //endregion




    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    public: virtual EulTokenType getType();
    public: virtual std::shared_ptr<EulType> getEulType(EulCodeGenContext* ctx, unsigned int someParam);
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
};
