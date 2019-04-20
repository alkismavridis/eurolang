#pragma once

/**
    This class represents a float token. Floats in EUL have a size.
*/
class EulFloatNode : public ValueNode {
    //region FIELDS
    public: double value;
    public: unsigned char size; //in bytes
    //endregion




    //region LIFE CYCLE
    public: EulFloatNode(double value, unsigned char size);
    public: EulFloatNode(char* text);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    public: bool isSymbolId();
    //endregion


    public: virtual EulNodeType getNodeType();
    public: virtual std::shared_ptr<EulType> getEulType(EulCodeGenContext* ctx, unsigned int someParam);
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
};
