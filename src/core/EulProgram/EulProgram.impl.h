
//region LIFE CYCLE
EulProgram::EulProgram() {
    this->initGlobals();
}


EulProgram::~EulProgram() {
    for (auto const& e : this->sources) delete e.second;
    for (auto const& e : this->globalDeclarations) delete e.second;
}


void EulProgram::initGlobals() {
    //Define basic Integer types
    this->globalDeclarations["Int8"] = new EulSymbol(yy::EulParser::token::VAL, "Int8", nullptr, new EulType("Int8"));
    this->globalDeclarations["Int16"] = new EulSymbol(yy::EulParser::token::VAL, "Int16", nullptr, new EulType("Int16"));
    this->globalDeclarations["Int32"] = new EulSymbol(yy::EulParser::token::VAL, "Int32", nullptr, new EulType("Int32"));
    this->globalDeclarations["Int64"] = new EulSymbol(yy::EulParser::token::VAL, "Int64", nullptr, new EulType("Int64"));
    this->globalDeclarations["Int"] = new EulSymbol(yy::EulParser::token::VAL, "Int", nullptr, new EulType("Int"));   //default size

    this->globalDeclarations["UInt8"] = new EulSymbol(yy::EulParser::token::VAL, "UInt8", nullptr, new EulType("UInt8"));
    this->globalDeclarations["UInt16"] = new EulSymbol(yy::EulParser::token::VAL, "UInt16", nullptr, new EulType("UInt16"));
    this->globalDeclarations["UInt32"] = new EulSymbol(yy::EulParser::token::VAL, "UInt32", nullptr, new EulType("UInt32"));
    this->globalDeclarations["UInt64"] = new EulSymbol(yy::EulParser::token::VAL, "UInt64", nullptr, new EulType("UInt64"));
    this->globalDeclarations["UInt"] = new EulSymbol(yy::EulParser::token::VAL, "UInt", nullptr, new EulType("UInt"));   //default size

    //Define basic Floating point types
    this->globalDeclarations["Float32"] = new EulSymbol(yy::EulParser::token::VAL, "Float32", nullptr, new EulType("Float32"));
    this->globalDeclarations["Float64"] = new EulSymbol(yy::EulParser::token::VAL, "Float64", nullptr, new EulType("Float64"));
    this->globalDeclarations["Float"] = new EulSymbol(yy::EulParser::token::VAL, "Float", nullptr, new EulType("Float")); //default size

    //Define basic text types
    this->globalDeclarations["Char8"] = new EulSymbol(yy::EulParser::token::VAL, "Char8", nullptr, new EulType("Char8"));
    this->globalDeclarations["Char16"] = new EulSymbol(yy::EulParser::token::VAL, "Char16", nullptr, new EulType("Char16"));
    this->globalDeclarations["Char32"] = new EulSymbol(yy::EulParser::token::VAL, "Char32", nullptr, new EulType("Char32"));
    this->globalDeclarations["Char64"] = new EulSymbol(yy::EulParser::token::VAL, "Char64", nullptr, new EulType("Char64"));
    this->globalDeclarations["Char"] = new EulSymbol(yy::EulParser::token::VAL, "Char", nullptr, new EulType("Char"));  //default size

    this->globalDeclarations["String"] = new EulSymbol(yy::EulParser::token::VAL, "String", nullptr, new EulType("String"));
}

void EulProgram::reset() {
    for (auto const& e : this->sources) delete e.second;
    for (auto const& e : this->globalDeclarations) delete e.second;

    this->sources.clear();
    this->globalDeclarations.clear();
}
//endregion




//region GLOBAL DECLARATIONS
//endregion




//region GETTERS
EulSourceFile* EulProgram::getSource(const std::string& id, unsigned char createIfNotExists) {
    //try finding the file
    auto entry = this->sources.find(id);
    if(entry != this->sources.end()) return entry->second;

    //we did not find the token. What we should now do, depends on createIfNotExists.
    if (!createIfNotExists) return 0;

    //we create a token, add it on our list, and return it.
    EulSourceFile* ret = new EulSourceFile(id, &this->globalDeclarations);
    this->sources[id] = ret;
    return ret;
}


/**
  Will be probably called by the Compiler object every time it needs to get the next source file.
  returns null if all files are parsed.
*/
EulSourceFile* EulProgram::nextPendingSource() {
    for (auto const& e : this->sources) {
        if ( !e.second->isParsed ) return e.second;
    }

    //all files are parsed. return null.
    return 0;
}
//endregion