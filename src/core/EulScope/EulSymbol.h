#pragma once

class EulSymbol {
    //region FIELDS
    public: int changeType; //one of yy::EulParser::token
    public: std::shared_ptr<EulType> varType;
    public: std::shared_ptr<EulToken> value;
    public: llvm::AllocaInst* allocInstruction;
    //endregion



    //region LIFE CYCLE
    public: EulSymbol(int changeType, std::shared_ptr<EulType> varType, std::shared_ptr<EulToken> value);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion
};