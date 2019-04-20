#pragma once

/**
    This class represents an int token. Ints in EUL have a size, and can be signed or unsigned.
*/
class EulBooleanNode : public ValueNode {
    //region FIELDS
    public: bool value;
    //endregion




    //region LIFE CYCLE
    public: EulBooleanNode(bool value);
    //endregion


    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion

    public: virtual EulNodeType getNodeType();

    public: bool isSymbolId();
    public: virtual std::shared_ptr<EulType> getEulType(EulCodeGenContext* ctx, unsigned int someParam);
    public: llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags);
};
