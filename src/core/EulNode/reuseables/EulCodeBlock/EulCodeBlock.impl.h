#pragma once



//region LIFE CYCLE
EulCodeBlock::EulCodeBlock(std::shared_ptr<std::vector<std::shared_ptr<EulStatement>>> statements, std::shared_ptr<EulScope> scope) {
    this->statements = statements;
    this->scope = scope;
}
//endregion



//region CORE FUNTIONS
EulNodeType EulCodeBlock::getNodeType() { return EulNodeType::CODE_BLOCK_TYPE; }
//endregion


//region CODE GENERATION
void EulCodeBlock::generateStatements(EulCodeGenContext* ctx) {
    for (auto instr : *this->statements) instr->performPreParsing(ctx);
    for (auto instr : *this->statements) instr->generateStatement(ctx);
}
//endregion



//region SERIALIZATION
void EulCodeBlock::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulCodeBlock TODO\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
