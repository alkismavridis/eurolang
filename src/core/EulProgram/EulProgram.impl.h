
//region LIFE CYCLE
EulProgram::EulProgram() : globalScope(nullptr) {
    this->llvmContext = new llvm::LLVMContext();
    this->globalModule = new llvm::Module("globalModule", *this->llvmContext);
    this->initGlobals();
}


EulProgram::~EulProgram() {
    for (auto const& e : this->sources) delete e.second;

    delete this->globalModule;
    delete this->llvmContext;
}


void EulProgram::initGlobals() {
    //Define basic Integer types
    this->globalScope.declare("Int8", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType(llvm::IntegerType::get(*this->llvmContext, 8)), 1));
    this->globalScope.declare("Int16", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType(llvm::IntegerType::get(*this->llvmContext, 16)), 1));
    this->globalScope.declare("Int32", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType(llvm::IntegerType::get(*this->llvmContext, 32)), 1));
    this->globalScope.declare("Int64", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType(llvm::IntegerType::get(*this->llvmContext, 64)), 1));
    this->globalScope.declare("Int", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType(llvm::IntegerType::get(*this->llvmContext, EUL_LANG_DEFAULT_INT_SIZE)), 1));

    //TODO unsigned?
    this->globalScope.declare("UInt8", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType(llvm::IntegerType::get(*this->llvmContext, 8)), 1));
    this->globalScope.declare("UInt16", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType(llvm::IntegerType::get(*this->llvmContext, 16)), 1));
    this->globalScope.declare("UInt32", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType(llvm::IntegerType::get(*this->llvmContext, 32)), 1));
    this->globalScope.declare("UInt64", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType(llvm::IntegerType::get(*this->llvmContext, 64)), 1));
    this->globalScope.declare("UInt", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType(llvm::IntegerType::get(*this->llvmContext, EUL_LANG_DEFAULT_INT_SIZE)), 1));


    /*
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

    this->globalScope.declare("String", new EulSymbol(yy::EulParser::token::VAL, nullptr, new EulType("String"), 1));*/
}

void EulProgram::reset() {
    for (auto const& e : this->sources) delete e.second;
    this->sources.clear();
    this->globalScope.reset();

    //reset the llvm entities
    //


    delete this->globalModule;
    delete this->llvmContext;
    this->llvmContext = new llvm::LLVMContext();
    this->globalModule = new llvm::Module("globalModule", *this->llvmContext);
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
    EulSourceFile* ret = new EulSourceFile(id, &this->globalScope, this->llvmContext);
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

EulSourceFile* EulProgram::getEntryPoint() {
    auto firstEntry = this->sources.begin();
    if (firstEntry == this->sources.end()) return nullptr;
    return firstEntry->second;
}
//endregion




//region GENERATOR SETUP
void EulProgram::makeMain(llvm::Module* module, llvm::IRBuilder<>* builder) {
    llvm::Function* mainFunc = (llvm::Function*)module->getOrInsertFunction("main", llvm::IntegerType::get(module->getContext(), 32), NULL);
    llvm::BasicBlock *block = llvm::BasicBlock::Create(module->getContext(), "entry", mainFunc);
    builder->SetInsertPoint(block);
}
//endregion



//region AST PARSING
void EulProgram::emmitObjCode(llvm::Module* module, const std::string& outputFileName) {
    //TODO we must deal with multiple modules being emmited.

    auto targetTriple = llvm::sys::getDefaultTargetTriple();

    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    std::string error;
    auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!target) {
        llvm:: errs() << error;
        return;
    }


    auto cpu = "generic";
    auto features = "";

    llvm::TargetOptions opt;
    auto rm = llvm::Optional<llvm::Reloc::Model>();
    auto targetMachine = target->createTargetMachine(targetTriple, cpu, features, opt, rm);

    module->setDataLayout(targetMachine->createDataLayout());
    module->setTargetTriple(targetTriple);

    std::error_code ec;
    llvm::raw_fd_ostream dest(outputFileName, ec, llvm::sys::fs::F_None);

    if (ec) {
        llvm::errs() << "Could not open file: " << ec.message();
        return;
    }

    llvm::legacy::PassManager pass;
    auto fileType = llvm::TargetMachine::CodeGenFileType::CGFT_ObjectFile;

    if (targetMachine->addPassesToEmitFile(pass, dest, fileType)) {
      llvm::errs() << "TargetMachine can't emit a file of this type";
      return;
    }

    pass.run(*module);
    dest.flush();
}


void EulProgram::emmitIRAssembly(llvm::Module* module, const std::string& outputFileName) {
    std::error_code code;
    llvm::raw_fd_ostream out(outputFileName, code, llvm::sys::fs::OpenFlags::F_None);

    module->dump();
    module->print(out, nullptr);
}
//endregion