
//region LIFE CYCLE
EulSourceFile::EulSourceFile(const std::string& id, std::map<std::string, EulSymbol*>* globalDeclarations) {
    this->isParsed = 0;
    this->id = id;
    this->globalDeclarations = globalDeclarations;
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




//region GETTERS
EulSymbol* EulSourceFile::getSymbol(const std::string& name) {
    //1. Search symbol in symbols vector
    auto entry = this->symbols.find(name);
    if (entry != this->symbols.end()) return entry->second;

    //2. If not found, search it in globalDeclarations
    entry = this->globalDeclarations->find(name);
    if (entry != this->globalDeclarations->end()) return entry->second;

    //3. Both failed. Return null
    return nullptr;
}
//endregion


std::ostream& operator<<(std::ostream& out, EulSourceFile* file) {
    out << "{" << std::endl;
    out << "\t\"type\":\"EulSourceFile\"," << std::endl;

    out << "\t\"statements\": ";
    EulToken::toJson(out, (std::vector<EulToken*>*) file->statements, 1);
    out << std::endl << "}";

    return out;
}
