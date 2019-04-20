#pragma once

class EulSymbol {
    //region FIELDS
    public: int changeType; //one of yy::EulParser::token
    public: std::shared_ptr<EulType> varType; //At the moment, not all symbols have a type. Primitive type symbols, for example give nullptr here. We might add a nativeTypeType in the future to cover this gap.
    public: std::shared_ptr<EulNode> value;
    public: llvm::Value* llvmValue;           //Think of this like the location of this symbol in memory, so that we know where to store stuff during assignment operations.
    //endregion



    //region LIFE CYCLE
    public: EulSymbol(int changeType, std::shared_ptr<EulType> varType, std::shared_ptr<EulNode> value);
    public: EulSymbol(int changeType, std::shared_ptr<EulType> varType, llvm::Value* llvmValue);
    public: EulSymbol(int changeType, std::shared_ptr<EulType> varType);
    //endregion



    //region SERIALIZING
    public: void toJson(std::ostream& out, int tabs);
    //endregion
};
