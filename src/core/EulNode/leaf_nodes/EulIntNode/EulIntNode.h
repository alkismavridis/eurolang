#pragma once

/**
    This class represents an int token. Ints in EUL have a size, and can be signed or unsigned.
*/
class EulIntNode : public ValueNode {
    //region FIELDS
    public: unsigned long int value;
    public: unsigned char size; //in bits
    public: bool isUnsigned;
    //endregion




    //region LIFE CYCLE
    public: EulIntNode(char* text);
    public: EulIntNode(unsigned long int value, unsigned char size, bool isUnsigned);
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    public: bool isSymbolId();
    //endregion



    public: virtual EulNodeType getNodeType();
    public: virtual std::shared_ptr<EulType> getEulType(EulCodeGenContext* ctx, unsigned int someParam);
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
};
