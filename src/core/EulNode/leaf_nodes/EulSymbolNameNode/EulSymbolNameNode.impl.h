#pragma once


//region LIFE CYCLE
EulSymbolNameNode::EulSymbolNameNode(const char* text, unsigned int length, std::shared_ptr<EulScope> scope) {
    this->name.assign(text, length);
    this->scope = scope;
}

EulSymbolNameNode::EulSymbolNameNode(const std::string& name, std::shared_ptr<EulScope> scope) {
    this->name = name;
    this->scope = scope;
}
//endregion



//region CORE FUNCTIONS
EulNodeType EulSymbolNameNode::getNodeType() { return EulNodeType::ID; }
bool EulSymbolNameNode::isSymbolId() { return true; }
//endregion



//region CODE GENERATION
llvm::Value* EulSymbolNameNode::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    //1. find the symbol in scope
    std::shared_ptr<EulSymbol> sym = this->scope->get(this->name);
    if (sym==nullptr) throw EulError(EulErrorType::SEMANTIC, this->name +": Symbol not found.");


    //2. We should either return the value as is, or load a variable and return the loading result:
    if (flags & EulCodeGenFlags_LOAD_VAR) {
        if (sym->llvmValue == nullptr)
            throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED Symbol with name "+ this->name +" does not have a value.");

        auto loadInstr = ctx->builder.CreateLoad(
            sym->llvmValue->getType()->getPointerElementType(),
            sym->llvmValue
        );

        return loadInstr;
    }
    else return sym->llvmValue;
}

std::shared_ptr<EulType> EulSymbolNameNode::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    std::shared_ptr<EulSymbol> sym = this->scope->get(this->name);
    if (sym==nullptr) throw EulError(EulErrorType::SEMANTIC, this->name +": Symbol not found.");

    return sym->varType;
}
//endregion



//region SERIALIZATION
void EulSymbolNameNode::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulSymbolNameNode\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"name\":\"" <<  this->name << "\"" << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
