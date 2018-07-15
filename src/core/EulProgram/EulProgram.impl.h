
//region LIFE CYCLE
EulProgram::EulProgram() : globalScope(nullptr) {
    this->initGlobals();
}


EulProgram::~EulProgram() {
    for (auto const& e : this->sources) delete e.second;
}


void EulProgram::initGlobals() {
    //Define basic Integer types
    this->globalScope.declare("Int8", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Int8"), 1));
    this->globalScope.declare("Int16", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Int16"), 1));
    this->globalScope.declare("Int32", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Int32"), 1));
    this->globalScope.declare("Int64", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Int64"), 1));
    this->globalScope.declare("Int", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Int"), 1));   //default size

    this->globalScope.declare("UInt8", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("UInt8"), 1));
    this->globalScope.declare("UInt16", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("UInt16"), 1));
    this->globalScope.declare("UInt32", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("UInt32"), 1));
    this->globalScope.declare("UInt64", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("UInt64"), 1));
    this->globalScope.declare("UInt", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("UInt"), 1));   //default size

    //Define basic Floating point types
    this->globalScope.declare("Float32", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Float32"), 1));
    this->globalScope.declare("Float64", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Float64"), 1));
    this->globalScope.declare("Float", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Float"), 1)); //default size

    //Define basic text types
    this->globalScope.declare("Char8", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Char8"), 1));
    this->globalScope.declare("Char16", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Char16"), 1));
    this->globalScope.declare("Char32", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Char32"), 1));
    this->globalScope.declare("Char64", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Char64"), 1));
    this->globalScope.declare("Char", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("Char"), 1));  //default size

    this->globalScope.declare("String", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("String"), 1));
}

void EulProgram::reset() {
    for (auto const& e : this->sources) delete e.second;
    this->sources.clear();
    this->globalScope.reset();
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
    EulSourceFile* ret = new EulSourceFile(id, &this->globalScope);
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