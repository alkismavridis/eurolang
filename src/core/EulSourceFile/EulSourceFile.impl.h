#pragma once


//region LIFE CYCLE
EulSourceFile::EulSourceFile(const std::string& id, EulScope* globalScope, llvm::LLVMContext* ctx) : scope(globalScope) {
    this->isParsed = 0;
    this->id = id;
    this->statements = nullptr;
}

EulSourceFile::~EulSourceFile() {
    //1. deinit statements
    if (this->statements != nullptr) {
        for (auto stmt : *this->statements) delete stmt;
        delete this->statements;
    }
}
//endregion




void EulSourceFile::parseAST(EulCodeGenContext* ctx) {
    //1. Parse every statement.
    for (auto stmt : *this->statements) stmt->generateStatement(ctx);
}

void EulSourceFile::doASTPreParsing(EulCodeGenContext* ctx) {
}



std::ostream& operator<<(std::ostream& out, EulSourceFile* file) {
    out << "{" << std::endl;
    out << "\t\"type\":\"EulSourceFile\"," << std::endl;

    out << "\t\"statements\": ";
    EulToken::toJson(out, (std::vector<EulToken*>*) file->statements, 1);
    out << std::endl << "}";

    return out;
}