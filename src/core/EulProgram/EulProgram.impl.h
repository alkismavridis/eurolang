
//region LIFE CYCLE
EulProgram::EulProgram() : globalScope(nullptr) {
    this->initGlobals();
}


EulProgram::~EulProgram() {
    for (auto const& e : this->sources) delete e.second;
}


void EulProgram::initGlobals() {
    //Define basic Integer types
    this->globalScope.declare("Int8", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, std::make_shared<EulType>(std::make_shared<EulIdToken>("i8", &this->globalScope))));
    this->globalScope.declare("Int16", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, std::make_shared<EulType>(std::make_shared<EulIdToken>("i16", &this->globalScope))));
    this->globalScope.declare("Int32", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, std::make_shared<EulType>(std::make_shared<EulIdToken>("i32", &this->globalScope))));
    this->globalScope.declare("Int64", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, std::make_shared<EulType>(std::make_shared<EulIdToken>("i64",  &this->globalScope))));
    this->globalScope.declare("Int", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, std::make_shared<EulType>(std::make_shared<EulIdToken>("i32", &this->globalScope))));

    this->globalScope.declare("UInt8", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, std::make_shared<EulType>(std::make_shared<EulIdToken>("i8", &this->globalScope))));
    this->globalScope.declare("UInt16", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, std::make_shared<EulType>(std::make_shared<EulIdToken>("i16", &this->globalScope))));
    this->globalScope.declare("UInt32", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, std::make_shared<EulType>(std::make_shared<EulIdToken>("i32", &this->globalScope))));
    this->globalScope.declare("UInt64", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, std::make_shared<EulType>(std::make_shared<EulIdToken>("i64", &this->globalScope))));
    this->globalScope.declare("UInt", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, std::make_shared<EulType>(std::make_shared<EulIdToken>("i32", &this->globalScope))));


    /*
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

EulSourceFile* EulProgram::getEntryPoint() {
    auto firstEntry = this->sources.begin();
    if (firstEntry == this->sources.end()) return nullptr;
    return firstEntry->second;
}
//endregion




//region GENERATOR SETUP
void EulProgram::declareClibSymbols(EulCodeGenContext* ctx) {
    auto type = llvm::FunctionType::get(
        llvm::Type::getVoidTy(ctx->context),
        llvm::ArrayRef<llvm::Type*>(llvm::IntegerType::get(ctx->context, 32)),
        false
    );
    ctx->module->getOrInsertGlobal("exit", type);
}


/**
    This represents the real entry point of the program. This function never returns.
    It just calls main, and then performs a system call in order to terminate.
*/
void EulProgram::makeEntryPoint(EulCodeGenContext* ctx) {
    llvm::Function* entryPointFnc = (llvm::Function*)ctx->module->getOrInsertFunction("_startEul", llvm::IntegerType::get(ctx->context, 32), NULL);
    llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx->context, "entry", entryPointFnc);
    ctx->builder.SetInsertPoint(block);


    //2. Call main
    auto mainFunc = (llvm::Function*)ctx->module->getOrInsertFunction("main", llvm::IntegerType::get(ctx->context, 32), NULL);
    auto mainReturnValue = ctx->builder.CreateCall(mainFunc);



    //3. call exit
    auto exitFunc = (llvm::Function*)ctx->module->getNamedValue("exit");
    ctx->builder.CreateCall(exitFunc, mainReturnValue);


    //5. Add return statement, just in case none was created already.
    auto zero = llvm::ConstantInt::get(llvm::IntegerType::get(ctx->context, 32), 0, true);
    ctx->builder.CreateRet(zero);

}

void EulProgram::makeMain(EulCodeGenContext* ctx) {
    llvm::Function* mainFunc = (llvm::Function*)ctx->module->getOrInsertFunction("main", llvm::IntegerType::get(ctx->context, 32), NULL);
    llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx->context, "entry", mainFunc);
    ctx->builder.SetInsertPoint(block);
}
//endregion



//region AST PARSING
void EulProgram::emmitObjCode(EulCodeGenContext* ctx, const std::string& outputFileName) {
    //TODO we must deal with multiple modules being emmited.

    auto targetTriple = llvm::sys::getDefaultTargetTriple();

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

    ctx->module->setDataLayout(targetMachine->createDataLayout());
    ctx->module->setTargetTriple(targetTriple);

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

    // Promote allocas to registers.
    pass.add(llvm::createPromoteMemoryToRegisterPass());
    // Do simple "peephole" optimizations and bit-twiddling optzns.
    pass.add(llvm::createInstructionCombiningPass());
    // Reassociate expressions.
    pass.add(llvm::createReassociatePass());
    // Eliminate Common SubExpressions.
    pass.add(llvm::createGVNPass());
    // Simplify the control flow graph (deleting unreachable blocks, etc).
    pass.add(llvm::createCFGSimplificationPass());

    pass.run(*ctx->module);
    dest.flush();
}


void EulProgram::emmitIRAssembly(EulCodeGenContext* ctx, const std::string& outputFileName) {
    std::error_code code;
    llvm::raw_fd_ostream out(outputFileName, code, llvm::sys::fs::OpenFlags::F_None);

    ctx->module->dump();
    ctx->module->print(out, nullptr);
}
//endregion