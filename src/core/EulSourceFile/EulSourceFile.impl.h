#pragma once


//region LIFE CYCLE
EulSourceFile::EulSourceFile(const std::string& id, EulScope* globalScope) : scope(globalScope) {
    this->isParsed = 0;
    this->id = id;
    this->statements = nullptr;
}
//endregion




void EulSourceFile::parseAST(EulCodeGenContext* ctx) {
    //1. Parse every statement.
    ctx->currentScope = &this->scope;
    for (auto stmt : *this->statements) stmt->generateStatement(ctx);
}

void EulSourceFile::doASTPreParsing(EulCodeGenContext* ctx) {
}



std::ostream& operator<<(std::ostream& out, EulSourceFile* file) {
    out << "{" << std::endl;
    out << "\t\"type\":\"EulSourceFile\"," << std::endl;

    out << "\t\"statements\": TODO";
    //auto castedVector = std::static_pointer_cast<std::vector<std::shared_ptr<EulToken>>>(file->statements);
    //EulToken::toJson(out, *castedVector.get(), 1);
    out << std::endl << "}";

    return out;
}