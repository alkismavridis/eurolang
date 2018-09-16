#pragma once

class EulSymbol {
    //region FIELDS
    public: int changeType; //one of yy::EulParser::token
    public: std::shared_ptr<EulType> varType;
    public: std::shared_ptr<EulToken> value;
    public: llvm::Value* llvmValue;
    //endregion



    //region LIFE CYCLE
    public: EulSymbol(int changeType, std::shared_ptr<EulType> varType, std::shared_ptr<EulToken> value);
    public: EulSymbol(int changeType, std::shared_ptr<EulType> varType, llvm::Value* llvmValue);
    public: EulSymbol(int changeType, std::shared_ptr<EulType> varType);
    //endregion



    //region SERIALIZING
    public: void toJson(std::ostream& out, int tabs);
    //endregion
};