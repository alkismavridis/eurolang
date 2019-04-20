#pragma once

/**
    This class represents a string token.
*/
class EulStringNode : public ValueNode {
    //region FIELDS
    public: std::string value;
    //endregion




    //region LIFE CYCLE
    public: EulStringNode(const std::string& buf);
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    public: bool isSymbolId();
    //endregion


    public: virtual EulNodeType getNodeType();
    public: virtual std::shared_ptr<EulType> getEulType(EulCodeGenContext* ctx, unsigned int someParam);
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
};
